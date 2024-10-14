# RAG from Scratch: Part 14 - ColBERT

Welcome to the 14th part of our RAG from scratch series, and today we're going to be talking about an approach called ColBERT.

## Introduction to ColBERT

We've discussed various approaches for indexing in our series. Just as a refresher, indexing falls right after query translation, routing, and query construction in our flow. Indexing is crucial for optimizing retrieval by creating efficient data structures for search.

### Previous Topics Covered:
- **Query Translation**: Translating a question to optimize retrieval.
- **Routing**: Directing the question to the appropriate data source.
- **Query Construction**: Converting natural language to domain-specific language for querying databases.

Today, we'll focus on an advanced embedding approach called ColBERT.

## ColBERT: Contextualized Late Interaction over BERT

### Problem with Traditional Embeddings

Traditional embedding models compress a document into a single vector, which can be overly restrictive. This compression might lose important nuances of the document.

![traditional-embedding](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/traditional-embedding.png)

### ColBERT's Approach

ColBERT addresses this by:
1. **Tokenization**: Breaking the document into tokens and creating an embedding for each token.
2. **Token-Level Similarity**: For each token in the question, computing the similarity across all tokens in the document.
3. **Max Similarity**: Taking the maximum similarity for each token in the question.
4. **Final Score**: Summing the maximum similarities to get the final score.

This method allows for a more granular and detailed comparison between the question and the document.


## Implementation in Code

RAGatouille makes it as simple to use ColBERT.

ColBERT generates a contextually influenced vector for each token in the passages.

ColBERT similarly generates vectors for each token in the query.

Then, the score of each document is the sum of the maximum similarity of each query embedding to any of the document embeddings:

### Step-by-Step Code Walkthrough

```python
! pip install -U ragatouille
```

```python
from ragatouille import RAGPretrainedModel
RAG = RAGPretrainedModel.from_pretrained("colbert-ir/colbertv2.0")
```

```python
import requests

def get_wikipedia_page(title: str):
    """
    Retrieve the full text content of a Wikipedia page.

    :param title: str - Title of the Wikipedia page.
    :return: str - Full text content of the page as raw string.
    """
    # Wikipedia API endpoint
    URL = "https://en.wikipedia.org/w/api.php"

    # Parameters for the API request
    params = {
        "action": "query",
        "format": "json",
        "titles": title,
        "prop": "extracts",
        "explaintext": True,
    }

    # Custom User-Agent header to comply with Wikipedia's best practices
    headers = {"User-Agent": "RAGatouille_tutorial/0.0.1 (ben@clavie.eu)"}

    response = requests.get(URL, params=params, headers=headers)
    data = response.json()

    # Extracting page content
    page = next(iter(data["query"]["pages"].values()))
    return page["extract"] if "extract" in page else None

full_document = get_wikipedia_page("Hayao_Miyazaki")
```

```python
RAG.index(
    collection=[full_document],
    index_name="Miyazaki-123",
    max_document_length=180,
    split_documents=True,
)
```
'.ragatouille/colbert/indexes/Miyazaki-123'

```python
results = RAG.search(query="What animation studio did Miyazaki found?", k=3)
results
```

[{'content': 'In April 1984, Miyazaki opened his own office in Suginami Ward, naming it Nibariki.\n\n\n=== Studio Ghibli ===\n\n\n==== Early films (1985–1996) ====\nIn June 1985, Miyazaki, Takahata, Tokuma and Suzuki founded the animation production company Studio Ghibli, with funding from Tokuma Shoten. Studio Ghibli\'s first film, Laputa: Castle in the Sky (1986), employed the same production crew of Nausicaä. Miyazaki\'s designs for the film\'s setting were inspired by Greek architecture and "European urbanistic templates".',
  'score': 25.903671264648438,
  'rank': 1,
  'document_id': '3a949f61-e976-4fc0-a272-d7bdbe777b21',
  'passage_id': 28},
 {'content': 'Hayao Miyazaki (宮崎 駿 or 宮﨑 駿, Miyazaki Hayao, Japanese: [mijaꜜzaki hajao]; born January 5, 1941) is a Japanese animator, filmmaker, and manga artist. A co-founder of Studio Ghibli, he has attained international acclaim as a masterful storyteller and creator of Japanese animated feature films, and is widely regarded as one of the most accomplished filmmakers in the history of animation.\nBorn in Tokyo City in the Empire of Japan, Miyazaki expressed interest in manga and animation from an early age, and he joined Toei Animation in 1963. During his early years at Toei Animation he worked as an in-between artist and later collaborated with director Isao Takahata.',
  'score': 25.571651458740234,
  'rank': 2,
  'document_id': '3a949f61-e976-4fc0-a272-d7bdbe777b21',
  'passage_id': 0},
 {'content': 'Glen Keane said Miyazaki is a "huge influence" on Walt Disney Animation Studios and has been "part of our heritage" ever since The Rescuers Down Under (1990). The Disney Renaissance era was also prompted by competition with the development of Miyazaki\'s films. Artists from Pixar and Aardman Studios signed a tribute stating, "You\'re our inspiration, Miyazaki-san!"',
  'score': 24.841182708740234,
  'rank': 3,
  'document_id': '3a949f61-e976-4fc0-a272-d7bdbe777b21',
  'passage_id': 76}]

```python
retriever = RAG.as_langchain_retriever(k=3)
retriever.invoke("What animation studio did Miyazaki found?")
```

[Document(page_content='In April 1984, Miyazaki opened his own office in Suginami Ward, naming it Nibariki.\n\n\n=== Studio Ghibli ===\n\n\n==== Early films (1985–1996) ====\nIn June 1985, Miyazaki, Takahata, Tokuma and Suzuki founded the animation production company Studio Ghibli, with funding from Tokuma Shoten. Studio Ghibli\'s first film, Laputa: Castle in the Sky (1986), employed the same production crew of Nausicaä. Miyazaki\'s designs for the film\'s setting were inspired by Greek architecture and "European urbanistic templates".'),
 Document(page_content='Hayao Miyazaki (宮崎 駿 or 宮﨑 駿, Miyazaki Hayao, Japanese: [mijaꜜzaki hajao]; born January 5, 1941) is a Japanese animator, filmmaker, and manga artist. A co-founder of Studio Ghibli, he has attained international acclaim as a masterful storyteller and creator of Japanese animated feature films, and is widely regarded as one of the most accomplished filmmakers in the history of animation.\nBorn in Tokyo City in the Empire of Japan, Miyazaki expressed interest in manga and animation from an early age, and he joined Toei Animation in 1963. During his early years at Toei Animation he worked as an in-between artist and later collaborated with director Isao Takahata.'),
 Document(page_content='Glen Keane said Miyazaki is a "huge influence" on Walt Disney Animation Studios and has been "part of our heritage" ever since The Rescuers Down Under (1990). The Disney Renaissance era was also prompted by competition with the development of Miyazaki\'s films. Artists from Pixar and Aardman Studios signed a tribute stating, "You\'re our inspiration, Miyazaki-san!"')]

### Useful links for reference

- https://arxiv.org/abs/2004.12832
- https://hackernoon.com/how-colbert-helps-developers-overcome-the-limits-of-rag
- https://til.simonwillison.net/llms/colbert-ragatouille
- https://github.com/stanford-futuredata/ColBERT
- https://github.com/AnswerDotAI/RAGatouille
- https://python.langchain.com/docs/integrations/retrievers/ragatouille/


## Conclusion

ColBERT is an advanced indexing approach that provides a more detailed and granular comparison between questions and documents by using token-level embeddings and similarity computations. This method can be particularly useful for longer documents and complex queries, offering strong performance and nuanced retrieval capabilities.

Thanks for following along!