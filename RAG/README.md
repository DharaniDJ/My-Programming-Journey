# RAG From Scratch Series

Welcome to the **RAG From Scratch** series by Lang Chain. This series provides a comprehensive guide to Retrieval-Augmented Generation (RAG), covering everything from basic principles to advanced techniques.

## What is RAG?

Retrieval-Augmented Generation (RAG) is a method that combines retrieval-based and generation-based approaches to improve the performance of language models. It involves three main stages:

1. **Indexing**: Splitting and embedding documents into a vector store.
2. **Retrieval**: Fetching relevant documents based on their semantic similarity to the input question.
3. **Generation**: Creating an answer using the retrieved documents.

RAG is used in various applications, including question answering, information retrieval, and conversational AI, where it enhances the ability of language models to provide accurate and contextually relevant responses.

## Series Overview

This series is divided into 14 parts, each focusing on a specific aspect of RAG:

### Part 1: Overview
Provides an introduction to RAG, its motivations, and the basic workflow involving indexing, retrieval, and generation.
[Read More](./Part%201%20(Overview).md)

### Part 2: Indexing
Deep dive into the indexing process, including splitting documents, embedding them, and storing them in a vector store.
[Read More](./Part%202%20(Indexing).md)

### Part 3: Retrieval
Explains the retrieval process, including embedding questions and performing similarity searches to fetch relevant documents.
[Read More](./Part%203%20(Retrieval).md)

### Part 4: Generation
Focuses on the generation stage, where answers are produced based on the retrieved documents.
[Read More](./Part%204%20(Generation).md)

### Part 5: Query Translation -- Multi Query
Introduces query translation and the multi-query approach, which involves rewriting queries from different perspectives to improve retrieval.
[Read More](./Part%205%20(Query%20Translation%20--%20Multi%20Query).md)

### Part 6: Query Translation -- RAG Fusion
Covers RAG Fusion, a method that includes a ranking step called Reciprocal Rank Fusion to aggregate and rank retrieved documents.
[Read More](./Part%206%20(Query%20Translation%20--%20RAG%20Fusion).md)

### Part 7: Query Translation -- Decomposition
Explores the decomposition approach, which involves breaking down a query into smaller, more manageable sub-questions.
[Read More](./Part%207%20(Query%20Translation%20--%20Decomposition).md)

### Part 8: Query Translation -- Step Back
Discusses the step-back approach, which involves making the query more abstract to address higher-level questions.
[Read More](./Part%208%20(Query%20Translation%20--%20Step%20Back).md)

### Part 9: Query Translation -- HyDE
Covers the HyDE approach, which involves hybrid decomposition and embedding techniques for query translation.
[Read More](./Part%209%20(Query%20Translation%20--%20HyDE).md)

### Part 10: Routing
Provides strategies for routing queries to the appropriate retrieval and generation pipelines.
[Read More](./Part%2010%20(Routing).md)

### Part 11: Query Structuring
Explores techniques for structuring queries to improve retrieval and generation performance.
[Read More](./Part%2011%20(Query%20Structuring).md)

### Part 12: Multi Representation Indexing
Discusses multi-representation indexing techniques for handling diverse document types and formats.
[Read More](./Part%2012%20(Multi-Representation%20Indexing).md)

### Part 13: RAPTOR
Covers the RAPTOR approach, which involves rapid and precise retrieval techniques for RAG pipelines.
[Read More](./Part%2013%20(RAPTOR).md)

### Part 14: ColBERT
Explores the ColBERT approach, which involves contextualized late interaction for efficient retrieval.
[Read More](./Part%2014%20(ColBERT).md)

## Conclusion

This series aims to provide a thorough understanding of RAG and its applications. Each part builds on the previous ones, gradually introducing more advanced concepts and techniques. Stay tuned for more in-depth tutorials and practical examples!

Thanks for following along!