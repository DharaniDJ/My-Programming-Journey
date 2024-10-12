# RAG From Scratch: Part 4 (Generation)

Welcome to the fourth video in the **RAG From Scratch** series by Lance from Lang Chain. This video focuses on **generation**, the final component of RAG pipelines following indexing and retrieval.

## Introduction to Generation

Generation involves producing an answer based on the documents retrieved in the previous stage. This process completes the basic RAG workflow:

1. **Indexing**: Splitting and embedding documents into a vector store.
2. **Retrieval**: Fetching relevant documents based on their semantic similarity to the input question.
3. **Generation**: Creating an answer using the retrieved documents.

### Generation Workflow

1. **Context Window**: Retrieved documents are packed into the LLM's context window.
2. **Prompt Template**: A prompt template is defined with placeholders for context and question.
3. **Chain Execution**: The prompt is populated with retrieved documents and the question, then passed to the LLM to generate an answer.

![generation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/generation.png)

## Part 4: Generation

Below is a quick code walkthrough for generation:

```python
from langchain_openai import ChatOpenAI
from langchain.prompts import ChatPromptTemplate

# Prompt
template = """Answer the question based only on the following context:
{context}

Question: {question}
"""

prompt = ChatPromptTemplate.from_template(template)
prompt
```

```python
# LLM
llm = ChatOpenAI(model_name="gpt-3.5-turbo", temperature=0)
```

```python
# Chain
chain = prompt | llm
```

```python
# Run
chain.invoke({"context":docs,"question":"What is Task Decomposition?"})
```

```python
from langchain import hub
prompt_hub_rag = hub.pull("rlm/rag-prompt")
```

```python
prompt_hub_rag
```

[RAG chains](https://python.langchain.com/docs/how_to/sequence/)

```python
from langchain_core.output_parsers import StrOutputParser
from langchain_core.runnables import RunnablePassthrough

rag_chain = (
    {"context": retriever, "question": RunnablePassthrough()}
    | prompt
    | llm
    | StrOutputParser()
)

rag_chain.invoke("What is Task Decomposition?")
```
### Useful links for reference

- https://python.langchain.com/docs/tutorials/rag/
- https://python.langchain.com/docs/how_to/sequence/
- https://smith.langchain.com/hub/rlm/rag-prompt?organizationId=1fa8b1f4-fcb9-4072-9aa9-983e35ad61b8
- https://python.langchain.com/docs/how_to/sequence/

## Conclusion

This readme provides a deep dive into the generation component of RAG pipelines. Next readme will explore more complex and detailed themes addressing limitations in this basic pipeline.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!