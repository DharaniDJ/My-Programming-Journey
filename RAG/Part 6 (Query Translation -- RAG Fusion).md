# RAG From Scratch: Part 6 (Query Translation -- RAG Fusion)

Welcome to the sixth part in the **RAG From Scratch** series. This readme focuses on **RAG Fusion**, a method for query translation in advanced RAG pipelines.

## Introduction to Query Translation

Query translation is an advanced stage in RAG pipelines aimed at improving retrieval by translating user queries. It involves several approaches:

1. **Rewriting**: Reframe the query from different perspectives.
2. **Sub-questions**: Break down the query into smaller, more manageable questions.
3. **Step-back**: Make the query more abstract to address higher-level questions.

### RAG Fusion

RAG Fusion is a specific rewriting approach that includes a clever ranking step called **Reciprocal Rank Fusion**. This method involves:

1. **Rewriting the Query**: Break the query into multiple differently worded questions.
2. **Retrieving Documents**: Perform retrieval for each rewritten query.
3. **Ranking Documents**: Use Reciprocal Rank Fusion to aggregate and rank the retrieved documents into a final consolidated list.

![consolidated-ranking](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/consolidated-ranking.png)

### Workflow

1. **Generate Multiple Queries**: Reframe the input question into multiple queries.
2. **Retrieve Documents**: Perform retrieval for each query.
3. **Rank Documents**: Use Reciprocal Rank Fusion to rank and consolidate the retrieved documents.
4. **Generate Final Answer**: Pass the ranked documents to the LLM to generate the final answer.

### Example Code

Below is a quick code walkthrough for the RAG Fusion approach:

#### Prompt
```python
from langchain.prompts import ChatPromptTemplate

# RAG-Fusion: Related
template = """You are a helpful assistant that generates multiple search queries based on a single input query. \n
Generate multiple search queries related to: {question} \n
Output (4 queries):"""
prompt_rag_fusion = ChatPromptTemplate.from_template(template)
```

```python
from langchain_core.output_parsers import StrOutputParser
from langchain_openai import ChatOpenAI

generate_queries = (
    prompt_rag_fusion 
    | ChatOpenAI(temperature=0)
    | StrOutputParser() 
    | (lambda x: x.split("\n"))
)
```

```python
from langchain.load import dumps, loads

def reciprocal_rank_fusion(results: list[list], k=60):
    """ Reciprocal_rank_fusion that takes multiple lists of ranked documents 
        and an optional parameter k used in the RRF formula """
    
    # Initialize a dictionary to hold fused scores for each unique document
    fused_scores = {}

    # Iterate through each list of ranked documents
    for docs in results:
        # Iterate through each document in the list, with its rank (position in the list)
        for rank, doc in enumerate(docs):
            # Convert the document to a string format to use as a key (assumes documents can be serialized to JSON)
            doc_str = dumps(doc)
            # If the document is not yet in the fused_scores dictionary, add it with an initial score of 0
            if doc_str not in fused_scores:
                fused_scores[doc_str] = 0
            # Retrieve the current score of the document, if any
            previous_score = fused_scores[doc_str]
            # Update the score of the document using the RRF formula: 1 / (rank + k)
            fused_scores[doc_str] += 1 / (rank + k)

    # Sort the documents based on their fused scores in descending order to get the final reranked results
    reranked_results = [
        (loads(doc), score)
        for doc, score in sorted(fused_scores.items(), key=lambda x: x[1], reverse=True)
    ]

    # Return the reranked results as a list of tuples, each containing the document and its fused score
    return reranked_results

retrieval_chain_rag_fusion = generate_queries | retriever.map() | reciprocal_rank_fusion
docs = retrieval_chain_rag_fusion.invoke({"question": question})
len(docs)
```

```python
from langchain_core.runnables import RunnablePassthrough

# RAG
template = """Answer the following question based on this context:

{context}

Question: {question}
"""

prompt = ChatPromptTemplate.from_template(template)

final_rag_chain = (
    {"context": retrieval_chain_rag_fusion, 
     "question": itemgetter("question")} 
    | prompt
    | llm
    | StrOutputParser()
)

final_rag_chain.invoke({"question":question})
```

Trace: https://smith.langchain.com/public/071202c9-9f4d-41b1-bf9d-86b7c5a7525b/r

### Useful links for reference

- https://github.com/Raudaschl/rag-fusion
- https://github.com/langchain-ai/langchain/blob/master/cookbook/rag_fusion.ipynb?ref=blog.langchain.dev
- https://towardsdatascience.com/forget-rag-the-future-is-rag-fusion-1147298d8ad1

## Conclusion

This readme provides a deep dive into the RAG Fusion approach for query translation in RAG pipelines. Next readme will explore other methods to improve retrieval and address limitations in this basic pipeline.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!
