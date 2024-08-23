# RAG From Scratch: Part 3 (Retrieval)

Welcome to the third part in the **RAG From Scratch** series. This readme focuses on **retrieval**, a key component of RAG pipelines alongside indexing and generation.

## Introduction to Retrieval

Retrieval involves fetching documents relevant to an input question based on their semantic similarity. This process follows the indexing stage, where documents are split, embedded, and stored in an index.

### Retrieval Workflow

1. **Embedding Documents**: Documents are embedded into a high-dimensional space based on their semantic content.
2. **Embedding Questions**: Questions are similarly embedded into the same space.
3. **Similarity Search**: A similarity search is performed to find documents near the question in this high-dimensional space.

![retrieval-semantic-search](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/retrieval-semantic-search.png)

### Conceptual Overview

- **Embedding Space**: Imagine embedding documents into a 3D space where each point represents the semantic meaning of a document.
- **Local Neighborhood Search**: Perform a search around the question's location in this space to find nearby documents with similar semantics.

![vectorstores](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/vectorstores.png)

![langchain-integrations](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/langchain-integrations.png)

## Part 3: Retrieval

Below is a quick code walkthrough for retrieval:

```python
# Index
from langchain_openai import OpenAIEmbeddings
from langchain_community.vectorstores import Chroma
vectorstore = Chroma.from_documents(documents=splits, 
                                    embedding=OpenAIEmbeddings())


retriever = vectorstore.as_retriever(search_kwargs={"k": 1})
```
```python
docs = retriever.get_relevant_documents("What is Task Decomposition?")
```
```python
len(docs)
```

### Useful links for reference

- https://simonwillison.net/2023/Oct/23/embeddings/
- https://www.pinecone.io/learn/series/faiss/hnsw/
- https://integrations.langchain.com/
- https://vdbs.superlinked.com/

## Conclusion

This readme provides a deep dive into the retrieval component of RAG pipelines. The next readme will focus on the generation stage, where answers are produced based on the retrieved documents.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!
