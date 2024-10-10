# RAG From Scratch: Part 5 (Query Translation -- Multi Query)

Welcome to the fifth part in the **RAG From Scratch** series. This readme focuses on **query translation**, specifically the **multi-query** approach.

![query-translation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/query-translation.png)

## Introduction to Query Translation

Query translation is an advanced stage in RAG pipelines aimed at improving retrieval by translating user queries. User queries can often be ambiguous or poorly written, leading to suboptimal retrieval results. Query translation helps address this issue.

![query-transformation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/query-transformation.png)

### Multi-Query Approach

The multi-query approach involves rewriting a query from different perspectives to increase the likelihood of retrieving relevant documents. This method improves retrieval reliability by considering nuances in how documents and questions are embedded.

![transform-into-multiple-perspectives](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/transform-into-multiple-perspectives.png)

### Workflow

1. **Reframe the Query**: Rewrite the query into multiple differently worded questions.
2. **Retrieve Documents**: Perform retrieval for each rewritten query.
3. **Combine Results**: Take the unique union of documents retrieved from all queries.

![improve-search](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/improve-search.png)

### Use this with parallelized retrieval

![parallelized-retrieval](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/parallelized-retrieval.png)

### Example Code

Below is a quick code walkthrough for the multi-query approach:

#### Index
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

# Split
from langchain.text_splitter import RecursiveCharacterTextSplitter
text_splitter = RecursiveCharacterTextSplitter.from_tiktoken_encoder(
    chunk_size=300, 
    chunk_overlap=50)

# Make splits
splits = text_splitter.split_documents(blog_docs)

# Index
from langchain_openai import OpenAIEmbeddings
from langchain_community.vectorstores import Chroma
vectorstore = Chroma.from_documents(documents=splits, 
                                    embedding=OpenAIEmbeddings())

retriever = vectorstore.as_retriever()
```

#### Prompt
```python
from langchain.prompts import ChatPromptTemplate

# Multi Query: Different Perspectives
template = """You are an AI language model assistant. Your task is to generate five 
different versions of the given user question to retrieve relevant documents from a vector 
database. By generating multiple perspectives on the user question, your goal is to help
the user overcome some of the limitations of the distance-based similarity search. 
Provide these alternative questions separated by newlines. Original question: {question}"""
prompt_perspectives = ChatPromptTemplate.from_template(template)

from langchain_core.output_parsers import StrOutputParser
from langchain_openai import ChatOpenAI

generate_queries = (
    prompt_perspectives 
    | ChatOpenAI(temperature=0) 
    | StrOutputParser() 
    | (lambda x: x.split("\n"))
)
```

```python
from langchain.load import dumps, loads

def get_unique_union(documents: list[list]):
    """ Unique union of retrieved docs """
    # Flatten list of lists, and convert each Document to string
    flattened_docs = [dumps(doc) for sublist in documents for doc in sublist]
    # Get unique documents
    unique_docs = list(set(flattened_docs))
    # Return
    return [loads(doc) for doc in unique_docs]

# Retrieve
question = "What is task decomposition for LLM agents?"
retrieval_chain = generate_queries | retriever.map() | get_unique_union
docs = retrieval_chain.invoke({"question":question})
len(docs)
```

```python
from operator import itemgetter
from langchain_openai import ChatOpenAI
from langchain_core.runnables import RunnablePassthrough

# RAG
template = """Answer the following question based on this context:

{context}

Question: {question}
"""

prompt = ChatPromptTemplate.from_template(template)

llm = ChatOpenAI(temperature=0)

final_rag_chain = (
    {"context": retrieval_chain, 
     "question": itemgetter("question")} 
    | prompt
    | llm
    | StrOutputParser()
)

final_rag_chain.invoke({"question":question})
```

### Useful links for reference

- https://twitter.com/abacaj/status/1652011519863926786?s=20
- https://python.langchain.com/docs/how_to/MultiQueryRetriever/


## Conclusion

This video provides a deep dive into the multi-query approach for query translation in RAG pipelines. Future videos will explore other methods to improve retrieval and address limitations in this basic pipeline.

Stay tuned for more in-depth tutorials on RAG!

Thanks for watching!
