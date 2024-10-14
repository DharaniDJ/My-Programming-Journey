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

RAGatouille makes it as simple to use ColBERT.

ColBERT generates a contextually influenced vector for each token in the passages.

ColBERT similarly generates vectors for each token in the query.

Then, the score of each document is the sum of the maximum similarity of each query embedding to any of the document embeddings:

## Implementation in Code

### Step-by-Step Code Walkthrough


### Useful links for reference

- 

## Conclusion

ColBERT is an advanced indexing approach that provides a more detailed and granular comparison between questions and documents by using token-level embeddings and similarity computations. This method can be particularly useful for longer documents and complex queries, offering strong performance and nuanced retrieval capabilities.

Thanks for following along!