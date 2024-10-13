# RAG from Scratch: Part 7 - Query Translation: Decomposition

Welcome to the seventh part in the **RAG From Scratch** series. This readme focuses on **Decomposition**, a method for query translation in advanced RAG pipelines.

## Introduction to Query Translation

Query translation in general is a set of approaches that sits towards the front of the overall RAG pipeline. The objective is to modify, rewrite, or otherwise decompose an input question from a user to improve retrieval. We've previously discussed various ways to do query rewriting, such as RAG fusion and multi-query.

## Decomposition

Decomposition involves breaking down an input question into a set of sub-questions. This technique is particularly useful for certain problems. For example, a paper from Google demonstrates the decomposition of the question "three words think machine learning" into three sub-questions: "think", "think machine", and "think machine learning". Each sub-question is solved individually, and the solutions are combined to form the final answer.

![decomposition](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/decomposition.png)

### Example: Last Letter Concatenation

In the example of last letter concatenation:
1. The input question "think machine learning" is decomposed into:
   - "think"
   - "think machine"
   - "think machine learning"
2. Each sub-question is solved individually:
   - "think" -> "k"
   - "think machine" -> "ke"
   - "think machine learning" -> "keg"
3. The final answer is "keg".

![last-letter-concatenation](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/last-letter-concatenation.png)

## Interleaved Retrieval and Chain of Thought Reasoning

A related approach called Interleaved Retrieval and Chain of Thought (IR-CoT) combines retrieval with chain of thought reasoning. This involves dynamically retrieving information to solve a set of sub-questions, using the answers from previous sub-questions to inform the next ones.

![ir-cot](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/ir-cot.png)

### Implementation in Code

Below is a quick code walkthrough for the Decomposition approach:

1. **Define a Prompt**: Create a prompt to break down an input question into sub-questions.
2. **Run the Decomposition**: Execute the prompt to see the decomposed questions.
3. **Solve Sub-Questions**: Use retrieval and prior question-answer pairs to solve each sub-question.

```python
from langchain.prompts import ChatPromptTemplate

# Decomposition
template = """You are a helpful assistant that generates multiple sub-questions related to an input question. \n
The goal is to break down the input into a set of sub-problems / sub-questions that can be answers in isolation. \n
Generate multiple search queries related to: {question} \n
Output (3 queries):"""
prompt_decomposition = ChatPromptTemplate.from_template(template)
```

```python
from langchain_openai import ChatOpenAI
from langchain_core.output_parsers import StrOutputParser

# LLM
llm = ChatOpenAI(temperature=0)

# Chain
generate_queries_decomposition = ( prompt_decomposition | llm | StrOutputParser() | (lambda x: x.split("\n")))

# Run
question = "What are the main components of an LLM-powered autonomous agent system?"
questions = generate_queries_decomposition.invoke({"question":question})
```

```python
questions
```

```
['1. What is LLM technology and how does it work in autonomous agent systems?',
 '2. What are the specific components that make up an LLM-powered autonomous agent system?',
 '3. How do the main components of an LLM-powered autonomous agent system interact with each other to enable autonomous functionality?']
```

Answer recursively

![decomposition-recursively](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/decomposition-recursively.png)

Papers:
- https://arxiv.org/pdf/2205.10625
- https://arxiv.org/abs/2212.10509

#### Prompt

```python
# Prompt
template = """Here is the question you need to answer:

\n --- \n {question} \n --- \n

Here is any available background question + answer pairs:

\n --- \n {q_a_pairs} \n --- \n

Here is additional context relevant to the question: 

\n --- \n {context} \n --- \n

Use the above context and any background question + answer pairs to answer the question: \n {question}
"""

decomposition_prompt = ChatPromptTemplate.from_template(template)
```

```python
from operator import itemgetter
from langchain_core.output_parsers import StrOutputParser

def format_qa_pair(question, answer):
    """Format Q and A pair"""
    
    formatted_string = ""
    formatted_string += f"Question: {question}\nAnswer: {answer}\n\n"
    return formatted_string.strip()

# llm
llm = ChatOpenAI(model_name="gpt-3.5-turbo", temperature=0)

q_a_pairs = ""
for q in questions:
    
    rag_chain = (
    {"context": itemgetter("question") | retriever, 
     "question": itemgetter("question"),
     "q_a_pairs": itemgetter("q_a_pairs")} 
    | decomposition_prompt
    | llm
    | StrOutputParser())

    answer = rag_chain.invoke({"question":q,"q_a_pairs":q_a_pairs})
    q_a_pair = format_qa_pair(q,answer)
    q_a_pairs = q_a_pairs + "\n---\n"+  q_a_pair
```

```python
answer
```

```python
'The main components of an LLM-powered autonomous agent system interact with each other in a coordinated manner to enable autonomous functionality. \n\n1. Planning: The agent breaks down complex tasks into smaller subgoals through task decomposition. This allows for efficient handling of tasks by breaking them down into manageable steps. The agent can also engage in self-reflection and refinement, learning from past actions and improving future results.\n\n2. Memory: The agent stores information and past experiences to inform future actions. This memory component helps the agent make informed decisions based on past experiences.\n\n3. External Classical Planner (LLM+P approach): In some cases, the agent may outsource long-horizon planning to an external classical planner using the Planning Domain Definition Language (PDDL) as an intermediate interface. This allows for more complex planning tasks to be handled efficiently.\n\n4. Self-Reflection (ReAct approach): The agent integrates reasoning and acting within LLM by extending the action space to include task-specific discrete actions and language prompts. This allows the agent to interact with the environment and generate reasoning traces in natural language. Self-reflection plays a crucial role in enabling the agent to improve iteratively by refining past actions and correcting mistakes.\n\nOverall, the interaction between these components enables the LLM-powered autonomous agent system to effectively plan, execute tasks, learn from experiences, and improve its performance over time, ultimately enabling autonomous functionality.'
```

Trace:

- Question 1: https://smith.langchain.com/public/faefde73-0ecb-4328-8fee-a237904115c0/r

- Question 2: https://smith.langchain.com/public/6142cad3-b314-454e-b2c9-15146cfcce78/r

- Question 3: https://smith.langchain.com/public/84bdca0f-0fa4-46d4-9f89-a7f25bd857fe/r

Answer individually (This is useful when the sub-questions are independent)

![decomposition-individually](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/decomposition-individually.png)

```python
# Answer each sub-question individually 

from langchain import hub
from langchain_core.prompts import ChatPromptTemplate
from langchain_core.runnables import RunnablePassthrough, RunnableLambda
from langchain_core.output_parsers import StrOutputParser
from langchain_openai import ChatOpenAI

# RAG prompt
prompt_rag = hub.pull("rlm/rag-prompt")

def retrieve_and_rag(question,prompt_rag,sub_question_generator_chain):
    """RAG on each sub-question"""
    
    # Use our decomposition / 
    sub_questions = sub_question_generator_chain.invoke({"question":question})
    
    # Initialize a list to hold RAG chain results
    rag_results = []
    
    for sub_question in sub_questions:
        
        # Retrieve documents for each sub-question
        retrieved_docs = retriever.get_relevant_documents(sub_question)
        
        # Use retrieved documents and sub-question in RAG chain
        answer = (prompt_rag | llm | StrOutputParser()).invoke({"context": retrieved_docs, 
                                                                "question": sub_question})
        rag_results.append(answer)
    
    return rag_results,sub_questions

# Wrap the retrieval and RAG process in a RunnableLambda for integration into a chain
answers, questions = retrieve_and_rag(question, prompt_rag, generate_queries_decomposition)
```

```python
def format_qa_pairs(questions, answers):
    """Format Q and A pairs"""
    
    formatted_string = ""
    for i, (question, answer) in enumerate(zip(questions, answers), start=1):
        formatted_string += f"Question {i}: {question}\nAnswer {i}: {answer}\n\n"
    return formatted_string.strip()

context = format_qa_pairs(questions, answers)

# Prompt
template = """Here is a set of Q+A pairs:

{context}

Use these to synthesize an answer to the question: {question}
"""

prompt = ChatPromptTemplate.from_template(template)

final_rag_chain = (
    prompt
    | llm
    | StrOutputParser()
)

final_rag_chain.invoke({"context":context,"question":question})
```

```
'The main components of an LLM-powered autonomous agent system include planning, subgoal decomposition, reflection and refinement, memory, task decomposition, and self-reflection. Planning involves breaking down tasks into manageable subgoals, while reflection allows for self-criticism and learning from past actions. Task decomposition can be done through simple prompting by LLM, task-specific instructions, or human inputs. These components work together to enable autonomous behavior by allowing the agent to plan, learn from mistakes, and improve its actions over time.'
```

Trace:

- https://smith.langchain.com/public/d8f26f75-3fb8-498a-a3a2-6532aa77f56b/r

### Useful links for reference

- https://github.com/Raudaschl/rag-fusion
- https://github.com/langchain-ai/langchain/blob/master/cookbook/rag_fusion.ipynb?ref=blog.langchain.dev
- https://towardsdatascience.com/forget-rag-the-future-is-rag-fusion-1147298d8ad1

## Conclusion

This readme provides a deep dive into the Decomposition approach for query translation in RAG pipelines. This approach can be tailored to specific problems, whether the sub-questions are dependent or independent.

Next readme will explore about step-back prompting to improve retrieval that builds on chain-of-thought reasoning.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!
