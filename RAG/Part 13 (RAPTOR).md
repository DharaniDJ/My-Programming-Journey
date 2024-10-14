# RAG from Scratch: Part 13 - RAPTOR

Welcome to the 13th part of our RAG from scratch series focused on a technique called RAPTOR.

## Introduction to RAPTOR

RAPTOR is a technique for hierarchical indexing within vector stores. It addresses the challenge of answering both low-level and high-level questions by building a hierarchical index of document summaries.

### Problem Statement

Some questions require detailed information from a single document or chunk (low-level questions), while others require consolidation across many documents or chunks (high-level questions). Traditional K-nearest neighbor retrieval may not suffice for high-level questions that need information from more than the set K parameter.

## RAPTOR Technique

### High-Level Intuition

1. **Document Clustering**: Start with a set of documents as leaves.
2. **Summarization**: Cluster similar documents and summarize each cluster.
3. **Recursive Summarization**: Continue clustering and summarizing recursively until you reach a limit or a single high-level summary.

This process creates a hierarchical index where both detailed and high-level summaries are indexed together. High-level questions will retrieve higher-level summaries, while low-level questions will retrieve more detailed chunks.

![RAPTOR](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/RAPTOR.png)

### Detailed Steps

1. **Load Documents**: Load the documents to be indexed.
2. **Generate Summaries**: Use an LLM to create summaries for each document.
3. **Set Up Vector Store and Document Store**: Store summaries in the vector store and full documents in the document store.
4. **Perform Retrieval**: Retrieve the summary from the vector store and use the doc ID to fetch the full document from the document store.

### Useful links for reference

- https://github.com/langchain-ai/langchain/blob/master/cookbook/RAPTOR.ipynb
- https://arxiv.org/pdf/2401.18059
- https://youtu.be/jbGchdTL7d0?si=kvcxS3Ati-dvNcRN

## Conclusion

RAPTOR is a powerful technique for hierarchical indexing, allowing for effective retrieval of both low-level and high-level information. By clustering and summarizing documents recursively, RAPTOR creates a comprehensive index that spans the abstraction hierarchy of question types. This approach is particularly useful for long-context LLMs, enabling efficient retrieval and generation of detailed answers.

Next readme will explore about ColBERT.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!