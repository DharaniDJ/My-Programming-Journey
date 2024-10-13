# RAG from Scratch: Part 9 - Query Translation: HyDE

Hi, this is Lance from LangChain. This is the fifth video focused on query translation in our RAG from scratch series. We're going to be talking about a technique called HyDE.

## Introduction to Query Translation

Query translation sits at the front of the overall RAG flow. The objective is to take an input question and translate it in a way that improves retrieval. HyDE is an interesting approach that leverages a simple idea: mapping questions into document space using hypothetical documents.

## The Concept of HyDE

The basic RAG flow involves embedding a question and a document, then looking for similarity between the embedded document and the embedded question. However, questions and documents are very different text objects. Documents can be large chunks from dense publications, while questions are short and potentially ill-worded.

![HyDE](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/HyDE.png)

### The Intuition Behind HyDE

The intuition behind HyDE is to take questions and map them into document space by generating a hypothetical document. This hypothetical document is closer to the desired document in the high-dimensional embedding space than the sparse raw input question itself. This translation makes the question better suited for retrieval.

![HyDE-intuition](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/HyDE-intuition.png)

## Implementation in Code

Let's walk through the implementation of HyDE.

1. **Define a Prompt**: Create a prompt to generate a hypothetical document.
2. **Generate Hypothetical Document**: Use the prompt to generate a hypothetical document.
3. **Perform Retrieval**: Retrieve documents related to the hypothetical document.
4. **Combine Results**: Combine the retrieved documents to produce the final answer.

### Step-by-Step Code Walkthrough

1. **Define the Prompt**: Create a prompt to generate a hypothetical document.

```python
from langchain.prompts import ChatPromptTemplate

# HyDE document genration
template = """Please write a scientific paper passage to answer the question
Question: {question}
Passage:"""
prompt_hyde = ChatPromptTemplate.from_template(template)

from langchain_core.output_parsers import StrOutputParser
from langchain_openai import ChatOpenAI

generate_docs_for_retrieval = (
    prompt_hyde | ChatOpenAI(temperature=0) | StrOutputParser()
)

# Run
question = "What is task decomposition for LLM agents?"
generate_docs_for_retrieval.invoke({"question":question})
```

2. **Perform Retrieval**: Retrieve documents related to the hypothetical document.

```python
# Retrieve
retrieval_chain = generate_docs_for_retrieval | retriever
retireved_docs = retrieval_chain.invoke({"question":question})
retireved_docs
```

3. **Combine Results**: Combine the retrieved documents to produce the final answer.

```python
# RAG
template = """Answer the following question based on this context:

{context}

Question: {question}
"""

prompt = ChatPromptTemplate.from_template(template)

final_rag_chain = (
    prompt
    | llm
    | StrOutputParser()
)

final_rag_chain.invoke({"context":retireved_docs,"question":question})
```

Papers:

- https://arxiv.org/pdf/2212.10496

### Useful links for reference

- https://github.com/langchain-ai/langchain/blob/master/cookbook/hypothetical_document_embeddings.ipynb

## Conclusion

HyDE is a useful technique for improving retrieval by generating hypothetical documents that map questions into document space. This approach can be particularly effective in domains with dense publications or technical documentation. By formulating higher-level documents, we can enhance the retrieval process and produce more comprehensive answers.

Next readme will explore about query routing (logical and semantic).

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!