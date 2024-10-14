# RAG from Scratch: Part 12 - Multi-Representation Indexing

Welcome to the 12th part of our RAG from scratch series focused indexing, specifically multi-representation indexing.

## Introduction to Indexing

We've previously discussed several key areas:
- **Query Translation**: Translating a question to optimize for retrieval.
- **Routing**: Directing the question to the appropriate data source (e.g., vector store, graph DB, SQL DB).
- **Query Construction**: Converting natural language into domain-specific language for querying sources.

![indexing](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/indexing.png)

Now, we'll focus on indexing techniques for vector stores, particularly multi-representation indexing.

## Multi-Representation Indexing

### Concept

The high-level idea is derived from a paper called "Proposition Indexing," which suggests decoupling raw documents from the units used for retrieval. Typically, you split a document and embed the split directly. However, this method involves using an LLM to produce a "proposition" or summary of the split, optimized for retrieval.

![proposition-indexing](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/proposition-indexing.png)

### Process

1. **Document Splitting**: Split the document.
2. **Summary Generation**: Use an LLM to create a summary of each split.
3. **Embedding**: Embed the summary for optimized retrieval.
4. **Storage**: Store the raw document separately in a document store.
5. **Retrieval**: Retrieve the summary from the vector store and use the doc ID to fetch the full document from the document store.

This approach allows the LLM to handle the entire document during generation, providing full context for answering questions.

![multi-representation-indexing](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/multi-representation-indexing.png)

## Implementation in Code

### Detailed Steps

1. **Load Documents**: Load the documents to be indexed.
2. **Generate Summaries**: Use an LLM to create summaries for each document.
3. **Set Up Vector Store and Document Store**: Store summaries in the vector store and full documents in the document store.
4. **Perform Retrieval**: Retrieve the summary from the vector store and use the doc ID to fetch the full document from the document store.

### Step-by-Step Code Walkthrough

```python
from langchain_community.document_loaders import WebBaseLoader
from langchain_text_splitters import RecursiveCharacterTextSplitter

loader = WebBaseLoader("https://lilianweng.github.io/posts/2023-06-23-agent/")
docs = loader.load()

loader = WebBaseLoader("https://lilianweng.github.io/posts/2024-02-05-human-data-quality/")
docs.extend(loader.load())
```

```python
import uuid

from langchain_core.documents import Document
from langchain_core.output_parsers import StrOutputParser
from langchain_core.prompts import ChatPromptTemplate
from langchain_openai import ChatOpenAI

chain = (
    {"doc": lambda x: x.page_content}
    | ChatPromptTemplate.from_template("Summarize the following document:\n\n{doc}")
    | ChatOpenAI(model="gpt-3.5-turbo",max_retries=0)
    | StrOutputParser()
)

summaries = chain.batch(docs, {"max_concurrency": 5})
```

```python
from langchain.storage import InMemoryByteStore
from langchain_openai import OpenAIEmbeddings
from langchain_community.vectorstores import Chroma
from langchain.retrievers.multi_vector import MultiVectorRetriever

# The vectorstore to use to index the child chunks
vectorstore = Chroma(collection_name="summaries",
                     embedding_function=OpenAIEmbeddings())

# The storage layer for the parent documents
store = InMemoryByteStore()
id_key = "doc_id"

# The retriever
retriever = MultiVectorRetriever(
    vectorstore=vectorstore,
    byte_store=store,
    id_key=id_key,
)
doc_ids = [str(uuid.uuid4()) for _ in docs]

# Docs linked to summaries
summary_docs = [
    Document(page_content=s, metadata={id_key: doc_ids[i]})
    for i, s in enumerate(summaries)
]

# Add
retriever.vectorstore.add_documents(summary_docs)
retriever.docstore.mset(list(zip(doc_ids, docs)))
```

```python
query = "Memory in agents"
sub_docs = vectorstore.similarity_search(query,k=1)
sub_docs[0]
```

Document(page_content='The document discusses the concept of building autonomous agents powered by Large Language Models (LLMs) as their core controllers. It covers components such as planning, memory, and tool use, along with case studies and proof-of-concept examples like AutoGPT and GPT-Engineer. Challenges like finite context length, planning difficulties, and reliability of natural language interfaces are also highlighted. The document provides references to related research papers and offers a comprehensive overview of LLM-powered autonomous agents.', metadata={'doc_id': 'cf31524b-fe6a-4b28-a980-f5687c9460ea'})

```python
retrieved_docs = retriever.get_relevant_documents(query,n_results=1)
retrieved_docs[0].page_content[0:500]
```

"\n\n\n\n\n\nLLM Powered Autonomous Agents | Lil'Log\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nLil'Log\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPosts\n\n\n\n\nArchive\n\n\n\n\nSearch\n\n\n\n\nTags\n\n\n\n\nFAQ\n\n\n\n\nemojisearch.app\n\n\n\n\n\n\n\n\n\n      LLM Powered Autonomous Agents\n    \nDate: June 23, 2023  |  Estimated Reading Time: 31 min  |  Author: Lilian Weng\n\n\n \n\n\nTable of Contents\n\n\n\nAgent System Overview\n\nComponent One: Planning\n\nTask Decomposition\n\nSelf-Reflection\n\n\nComponent Two: Memory\n\nTypes of Memory\n\nMaximum Inner Product Search (MIPS)\n\n"

### Useful links for reference

- https://www.youtube.com/watch?v=8OJC21T2SL4
- https://blog.langchain.dev/semi-structured-multi-modal-rag/
- https://python.langchain.com/docs/how_to/multi_vector/
- https://arxiv.org/abs/2312.06648
- https://python.langchain.com/docs/how_to/parent_document_retriever/
- https://blog.langchain.dev/multi-modal-rag-template/

## Conclusion

Multi-representation indexing is a powerful technique for optimizing retrieval by using summaries to represent documents in a vector store while storing the full documents separately. This approach leverages the strengths of LLMs to provide full context during generation, making it particularly useful for long-context LLMs.

Next readme will explore about RAPTOR.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!