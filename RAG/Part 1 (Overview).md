# RAG From Scratch: Part 1 (Overview)

Welcome to the **RAG From Scratch** series! This series, will walk you through the basic principles of Retrieval-Augmented Generation (RAG) and build up to advanced topics.

## Introduction to RAG

RAG is motivated by the fact that large language models (LLMs) haven't seen all the data you may care about, such as private or very recent data. Despite being pre-trained on a vast number of tokens, LLMs are limited in their knowledge of specific or up-to-date information.

![world-data](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/world-data.png)

### Key Concepts

1. **Context Windows**: LLMs have context windows that are getting increasingly large, allowing them to fit information from external sources.
2. **Kernel of a New Operating System**: LLMs can be thought of as the kernel of a new kind of operating system, with the ability to connect to external data being a central capability.

![kernal-to-external-data](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/kernal-to-external-data.png)

## RAG Workflow

RAG typically involves three stages:

1. **Indexing**: External documents are indexed so they can be easily retrieved based on an input query.
2. **Retrieval**: Relevant documents are retrieved based on the input query.
3. **Generation**: Retrieved documents are fed into an LLM to produce an answer grounded in those documents.

![retrieval-augmented-generation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/retrieval-augmented-generation.png)

## Future Topics

The following readme's will cover the following:

- Basic ideas behind indexing, retrieval, and generation.
- Advanced topics and tricks that build on these basic components like
    - Query Transformation
    - Routing
    - Query Construction
    - Indexing
    - Retrieval
    - Generation

![RAG-overall-roadmap](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/RAG-overall-roadmap.png)

## Interactive Code Walkthrough

The readme includes interactive code walkthroughs. Below is a quick overview of the RAG quick start code:

1. **Loading Documents**: Load documents (e.g., a blog post) and split them into chunks.
2. **Embedding and Indexing**: Each chunk is embedded and indexed into a vector store.
3. **Retriever and Prompt**: Define a retriever and a prompt for RAG.
4. **LLM and Chain Setup**: Set up the LLM and the chain to process the input question, retrieve relevant documents, and generate an answer.

### Example Code

### Environment

`(1) Packages`
```bash
!pip install langchain_community tiktoken langchain-openai langchainhub chromadb langchain
```

`(2) LangSmith`

[https://docs.smith.langchain.com/](https://docs.smith.langchain.com/)

```python
import os
os.environ['LANGCHAIN_TRACING_V2'] = 'true'
os.environ['LANGCHAIN_ENDPOINT'] = 'https://api.smith.langchain.com'
os.environ['LANGCHAIN_API_KEY'] = '<your-api-key>'
```

`(3) API Keys`
```python
os.environ['OPENAI_API_KEY'] = '<your-api-key>'
```

### Observability with LSmith

Using LangSmith for tracing and observability is recommended, especially when building RAG pipelines. You can see the input question, retrieved documents, and the final prompt passed to the LLM.

## Part 1: Overview
[RAG quickstart](https://python.langchain.com/docs/tutorials/rag/)

```python
import bs4
from langchain import hub
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_community.document_loaders import WebBaseLoader
from langchain_community.vectorstores import Chroma
from langchain_core.output_parsers import StrOutputParser
from langchain_core.runnables import RunnablePassthrough
from langchain_openai import ChatOpenAI, OpenAIEmbeddings

#### INDEXING ####

# Load Documents
loader = WebBaseLoader(
    web_paths=("https://lilianweng.github.io/posts/2023-06-23-agent/",),
    bs_kwargs=dict(
        parse_only=bs4.SoupStrainer(
            class_=("post-content", "post-title", "post-header")
        )
    ),
)
docs = loader.load()

# Split
text_splitter = RecursiveCharacterTextSplitter(chunk_size=1000, chunk_overlap=200)
splits = text_splitter.split_documents(docs)

# Embed
vectorstore = Chroma.from_documents(documents=splits, 
                                    embedding=OpenAIEmbeddings())

retriever = vectorstore.as_retriever()

#### RETRIEVAL and GENERATION ####

# Prompt
prompt = hub.pull("rlm/rag-prompt")

# LLM
llm = ChatOpenAI(model_name="gpt-3.5-turbo", temperature=0)

# Post-processing
def format_docs(docs):
    return "\n\n".join(doc.page_content for doc in docs)

# Chain
rag_chain = (
    {"context": retriever | format_docs, "question": RunnablePassthrough()}
    | prompt
    | llm
    | StrOutputParser()
)

# Question
rag_chain.invoke("What is Task Decomposition?")
```

## Conclusion

This overview provides a general understanding of how RAG works. Future readme will break down each component in more detail. Stay tuned for more in-depth tutorials!

Thanks for reading!

Feel free to explore the repository and follow along with the series to deepen your understanding of RAG. Happy coding!