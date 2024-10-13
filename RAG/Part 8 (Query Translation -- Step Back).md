# RAG from Scratch: Part 7 - Query Translation: Step Back

Welcome to the eighth part in the **RAG From Scratch** series.  In our deep dive on query translation, and we're going to be focused on step back prompting.

## Introduction to Query Translation

Query translation sits at the first stage of a RAG pipeline. The main aim is to take an input question and translate or modify it to improve retrieval. We've explored several approaches, such as rewriting a question using RAG fusion and multi-query, and breaking down a question into sub-questions for independent solving.

## Step Back Prompting

Step back prompting takes the opposite approach by asking a more abstract question. This technique, presented by Google, uses few-shot prompting to produce step back or more abstract questions. The method involves providing examples of step back questions given the original question.

![step-back](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/step-back.png)

### Example of Step Back Prompting

For instance, instead of asking a specific question like "In what year was the region where the country is located created?", a step back question would be "What is the general history of this region?". This approach abstracts the question to a higher level, making it easier to retrieve relevant information.

![few-shot-prompt](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/few-shot-prompt.png)

### Implementation in Code

Below is a quick code walkthrough for the Step-back approach:

1. **Formulate the Prompt**: Create a prompt using few-shot examples from the paper.
2. **Generate Step Back Question**: Use the prompt to generate a step back question.
3. **Perform Retrieval**: Retrieve documents related to both the original and step back questions.
4. **Combine Results**: Combine the retrieved documents to produce the final answer.

```python
# Define the prompt template
prompt_template = """
You are an expert in world knowledge. I asked you a question. Your response should be comprehensive and not contradict the following examples:
Original Question: {original_question}
Step Back Question: {step_back_question}
"""

# Example question
original_question = "What is task composition for LLM agents?"

# Generate step back question
step_back_question = "What is the process of task composition?"

# Define a function to perform retrieval (placeholder)
def perform_retrieval(question):
    # Implement retrieval logic here
    return f"Documents related to '{question}'"

# Perform retrieval on both questions
original_retrieval = perform_retrieval(original_question)
step_back_retrieval = perform_retrieval(step_back_question)

# Combine the results
combined_results = f"{original_retrieval}\n{step_back_retrieval}"

# Print the combined results
print(combined_results)
```

### Detailed Steps

1. **Formulate the Prompt**: Use few-shot examples to create a prompt that generates a step back question.
2. **Generate Step Back Question**: Use the prompt to generate a more abstract question.
3. **Perform Retrieval**: Retrieve documents related to both the original and step back questions.
4. **Combine Results**: Combine the retrieved documents to produce a comprehensive answer.

```python
## Few Shot Examples
from langchain_core.prompts import ChatPromptTemplate, FewShotChatMessagePromptTemplate
examples = [
    {
        "input": "Could the members of The Police perform lawful arrests?",
        "output": "what can the members of The Police do?",
    },
    {
        "input": "Jan Sindel’s was born in what country?",
        "output": "what is Jan Sindel’s personal history?",
    },
]
# We now transform these to example messages
example_prompt = ChatPromptTemplate.from_messages(
    [
        ("human", "{input}"),
        ("ai", "{output}"),
    ]
)
few_shot_prompt = FewShotChatMessagePromptTemplate(
    example_prompt=example_prompt,
    examples=examples,
)
prompt = ChatPromptTemplate.from_messages(
    [
        (
            "system",
            """You are an expert at world knowledge. Your task is to step back and paraphrase a question to a more generic step-back question, which is easier to answer. Here are a few examples:""",
        ),
        # Few shot examples
        few_shot_prompt,
        # New question
        ("user", "{question}"),
    ]
)
```

```python
generate_queries_step_back = prompt | ChatOpenAI(temperature=0) | StrOutputParser()
question = "What is task decomposition for LLM agents?"
generate_queries_step_back.invoke({"question": question})
```

```python
# Response prompt 
response_prompt_template = """You are an expert of world knowledge. I am going to ask you a question. Your response should be comprehensive and not contradicted with the following context if they are relevant. Otherwise, ignore them if they are not relevant.

# {normal_context}
# {step_back_context}

# Original Question: {question}
# Answer:"""
response_prompt = ChatPromptTemplate.from_template(response_prompt_template)

chain = (
    {
        # Retrieve context using the normal question
        "normal_context": RunnableLambda(lambda x: x["question"]) | retriever,
        # Retrieve context using the step-back question
        "step_back_context": generate_queries_step_back | retriever,
        # Pass on the question
        "question": lambda x: x["question"],
    }
    | response_prompt
    | ChatOpenAI(temperature=0)
    | StrOutputParser()
)

chain.invoke({"question": question})
```

Papers:

- https://arxiv.org/pdf/2310.06117

## Conclusion

Step back prompting is a useful technique for improving retrieval by asking more abstract questions. This approach can be particularly effective in domains with a lot of conceptual knowledge, such as textbooks or technical documentation. By formulating higher-level questions, we can enhance the retrieval process and produce more comprehensive answers.

Next readme will explore about HyDE(Hypothetical Document Embeddings) to improve retrieval that generates hypothetical documents that could be used to answer the user input question.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!