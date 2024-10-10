# RAG From Scratch: Part 2 (Indexing)

Welcome to the second part in the **RAG From Scratch** series. This readme focuses on **indexing**, one of the main components of RAG pipelines alongside retrieval and generation.

## Introduction to Indexing

Indexing involves loading external documents and putting them into a retriever. The goal of the retriever is to fetch documents related to an input question based on their relevance or similarity.

![document-loading](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/document-loading.png)

### Numerical Representation of Documents

To establish the relationship between documents and queries, we use numerical representations. This makes it easier to compare documents using vectors rather than free-form text.

![numerical-representation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/numerical-representation.png)

#### Statistical representations

- Developed using statistical methods.
- Represent documents based on word frequency.
- Large vocabulary with many zeros (sparse).

#### Machine Learned representation

- Machine-learned methods to compress documents into fixed-length vectors.
- Capture the semantic meaning of documents.
- Strong search methods over embeddings.

![statistical-ml-representation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/statistical-ml-representation.png)

## Indexing Workflow

1. **Splitting Documents**: Documents are split into chunks due to the limited context windows of embedding models.
2. **Embedding Documents**: Each chunk is compressed into a vector that captures its semantic meaning.
3. **Indexing Vectors**: Vectors are indexed for efficient retrieval.

![load-split-embed](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/load-split-embed.png)

## Part 2: Indexing

Below is a quick code walkthrough for indexing:

```python
# Documents
question = "What kinds of pets do I like?"
document = "My favorite pet is a cat."
```

[Count tokens](https://github.com/openai/openai-cookbook/blob/main/examples/How_to_count_tokens_with_tiktoken.ipynb) considering [~4 char / token](https://help.openai.com/en/articles/4936856-what-are-tokens-and-how-to-count-them)

```python
import tiktoken

def num_tokens_from_string(string: str, encoding_name: str) -> int:
    """Returns the number of tokens in a text string."""
    encoding = tiktoken.get_encoding(encoding_name)
    num_tokens = len(encoding.encode(string))
    return num_tokens

num_tokens_from_string(question, "cl100k_base")
```

[Text embedding models](https://python.langchain.com/docs/integrations/text_embedding/openai/)

```python
from langchain_openai import OpenAIEmbeddings
embd = OpenAIEmbeddings()
query_result = embd.embed_query(question)
document_result = embd.embed_query(document)
len(query_result)
```

[Cosine similarity](https://platform.openai.com/docs/guides/embeddings/faq) is recommended (1 indicates idential) for OpenAI embeddings

```python
import numpy as np

def cosine_similarity(vec1, vec2):
    dot_product = np.dot(vec1, vec2)
    norm_vec1 = np.linalg.norm(vec1)
    norm_vec2 = np.linalg.norm(vec2)
    return dot_product / (norm_vec1 * norm_vec2)

similarity = cosine_similarity(query_result, document_result)
print("Cosine Similarity:", similarity)
```

[Document Loader](https://python.langchain.com/docs/integrations/document_loaders/)

```python
#### INDEXING ####

# Load blog
import bs4
from langchain_community.document_loaders import WebBaseLoader
loader = WebBaseLoader(
    web_paths=("https://lilianweng.github.io/posts/2023-06-23-agent/",),
    bs_kwargs=dict(
        parse_only=bs4.SoupStrainer(
            class_=("post-content", "post-title", "post-header")
        )
    ),
)
blog_docs = loader.load()
```

[Splitter](https://python.langchain.com/docs/how_to/recursive_text_splitter/)
- This text splitter is the recommended one for generic text. It is parameterized by a list of characters. It tries to split on them in order until the chunks are small enough. The default list is ["\n\n", "\n", " ", ""]. This has the effect of trying to keep all paragraphs (and then sentences, and then words) together as long as possible, as those would generically seem to be the strongest semantically related pieces of text.
```python
# Split
from langchain.text_splitter import RecursiveCharacterTextSplitter
text_splitter = RecursiveCharacterTextSplitter.from_tiktoken_encoder(
    chunk_size=300, 
    chunk_overlap=50)

# Make splits
splits = text_splitter.split_documents(blog_docs)
```

[Vectorstores](https://python.langchain.com/docs/integrations/vectorstores/)

```python
# Split
from langchain.text_splitter import RecursiveCharacterTextSplitter
text_splitter = RecursiveCharacterTextSplitter.from_tiktoken_encoder(
    chunk_size=300, 
    chunk_overlap=50)

# Make splits
splits = text_splitter.split_documents(blog_docs)
```
### Useful links for reference

- https://integrations.langchain.com/
- https://simonwillison.net/2023/Oct/23/embeddings/
- https://www.pinecone.io/learn/series/nlp/dense-vector-embeddings-nlp/
- https://cameronrwolfe.substack.com/p/the-basics-of-ai-powered-vector-search?utm_source=profile&utm_medium=reader2
- https://chunkviz.up.railway.app/
- https://www.youtube.com/watch?v=8OJC21T2SL4

- https://github.com/openai/openai-cookbook/blob/main/examples/How_to_count_tokens_with_tiktoken.ipynb
- https://help.openai.com/en/articles/4936856-what-are-tokens-and-how-to-count-them
- https://python.langchain.com/docs/integrations/text_embedding/openai/
- https://platform.openai.com/docs/guides/embeddings/faq
- https://python.langchain.com/docs/integrations/document_loaders/
- https://python.langchain.com/docs/how_to/recursive_text_splitter/
- https://python.langchain.com/docs/integrations/vectorstores/

## Conclusion

This readme provides a deep dive into the indexing component of RAG pipelines. The next readme will focus on retrieval using the indexed vectors.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!
