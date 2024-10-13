# RAG from Scratch: Part 10 - Routing

Welcome to 10th part in our RAG from scratch series focused on routing.

## Introduction to Routing

We've talked through query translation, which involves taking a question and translating it in some way, such as decomposing it or using step back prompting, to improve retrieval. Routing is the next step, where we route the potentially decomposed question to the right source. This could mean different databases or other data sources.

![routing](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/routing.png)

## Types of Routing

### Logical Routing

Logical routing involves giving an LLM knowledge of the various data sources and letting it reason about which one to apply the question to. This is akin to classification plus function calling to produce a structured output constrained to specific possibilities.

#### Example: Logical Routing

1. **Define Data Sources**: Python docs, JS docs, GoLang docs.
2. **Set Up Data Model**: Bind the data model to the LLM to output one of the three options.
3. **Generate Structured Output**: The LLM invokes a function to produce an output adhering to the schema.

![logical-routing](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/logical-routing.png)

### Semantic Routing

Semantic routing involves embedding the question and prompts, computing the similarity between them, and choosing a prompt based on the similarity.

#### Example: Semantic Routing

1. **Embed Prompts**: Physics prompt, Math prompt.
2. **Compute Similarity**: Embed the question and compute similarity with the prompts.
3. **Choose Prompt**: Select the prompt based on the highest similarity.

![semantic-routing](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/semantic-routing.png)

## Implementation in Code

### Logical Routing

1. **Define Structured Object**: Create a structured object for the LLM to output.
2. **Bind to LLM**: Convert the object into a function schema and bind it to the LLM.
3. **Route Question**: Use the LLM to classify the question and route it to the appropriate data source.

```python
from typing import Literal

from langchain_core.prompts import ChatPromptTemplate
from langchain_core.pydantic_v1 import BaseModel, Field
from langchain_openai import ChatOpenAI

# Data model
class RouteQuery(BaseModel):
    """Route a user query to the most relevant datasource."""

    datasource: Literal["python_docs", "js_docs", "golang_docs"] = Field(
        ...,
        description="Given a user question choose which datasource would be most relevant for answering their question",
    )

# LLM with function call 
llm = ChatOpenAI(model="gpt-3.5-turbo-0125", temperature=0)
structured_llm = llm.with_structured_output(RouteQuery)

# Prompt 
system = """You are an expert at routing a user question to the appropriate data source.

Based on the programming language the question is referring to, route it to the relevant data source."""

prompt = ChatPromptTemplate.from_messages(
    [
        ("system", system),
        ("human", "{question}"),
    ]
)

# Define router 
router = prompt | structured_llm
```
Note: we used function calling to produce structured output.


![routing-structured-output](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/routing-structured-output.png)

```python
question = """Why doesn't the following code work:

from langchain_core.prompts import ChatPromptTemplate

prompt = ChatPromptTemplate.from_messages(["human", "speak in {language}"])
prompt.invoke("french")
"""

result = router.invoke({"question": question})
```

```python
result
```

RouteQuery(datasource='python_docs')

```python
result.datasource
```


'python_docs'

- Once we have this, it is trivial to define a branch that uses result.datasource

```python
def choose_route(result):
    if "python_docs" in result.datasource.lower():
        ### Logic here 
        return "chain for python_docs"
    elif "js_docs" in result.datasource.lower():
        ### Logic here 
        return "chain for js_docs"
    else:
        ### Logic here 
        return "golang_docs"

from langchain_core.runnables import RunnableLambda

full_chain = router | RunnableLambda(choose_route)
```

```python
full_chain.invoke({"question": question})
```

'chain for python_docs'


Trace:
- https://smith.langchain.com/public/c2ca61b4-3810-45d0-a156-3d6a73e9ee2a/r

### Semantic Routing

1. **Embed Prompts**: Embed the prompts.
2. **Embed Question**: Embed the question.
3. **Compute Similarity**: Compute similarity between the question and the prompts.
4. **Choose Prompt**: Select the prompt based on the highest similarity.

```python
from langchain.utils.math import cosine_similarity
from langchain_core.output_parsers import StrOutputParser
from langchain_core.prompts import PromptTemplate
from langchain_core.runnables import RunnableLambda, RunnablePassthrough
from langchain_openai import ChatOpenAI, OpenAIEmbeddings

# Two prompts
physics_template = """You are a very smart physics professor. \
You are great at answering questions about physics in a concise and easy to understand manner. \
When you don't know the answer to a question you admit that you don't know.

Here is a question:
{query}"""

math_template = """You are a very good mathematician. You are great at answering math questions. \
You are so good because you are able to break down hard problems into their component parts, \
answer the component parts, and then put them together to answer the broader question.

Here is a question:
{query}"""

# Embed prompts
embeddings = OpenAIEmbeddings()
prompt_templates = [physics_template, math_template]
prompt_embeddings = embeddings.embed_documents(prompt_templates)

# Route question to prompt 
def prompt_router(input):
    # Embed question
    query_embedding = embeddings.embed_query(input["query"])
    # Compute similarity
    similarity = cosine_similarity([query_embedding], prompt_embeddings)[0]
    most_similar = prompt_templates[similarity.argmax()]
    # Chosen prompt 
    print("Using MATH" if most_similar == math_template else "Using PHYSICS")
    return PromptTemplate.from_template(most_similar)


chain = (
    {"query": RunnablePassthrough()}
    | RunnableLambda(prompt_router)
    | ChatOpenAI()
    | StrOutputParser()
)

print(chain.invoke("What's a black hole"))
```

Using PHYSICS
A black hole is a region in space where the gravitational pull is so strong that nothing, not even light, can escape from it. It is formed when a massive star collapses in on itself. The boundary surrounding a black hole is called the event horizon. Beyond the event horizon, the gravitational pull is so intense that even time and space are distorted. Black holes are some of the most mysterious and fascinating objects in the universe.

Trace:
- https://smith.langchain.com/public/98c25405-2631-4de8-b12a-1891aded3359/r

### Useful links for reference

- https://python.langchain.com/docs/tutorials/query_analysis/
- https://python.langchain.com/docs/how_to/routing/

## Conclusion

Routing is a crucial step in the RAG pipeline, ensuring that questions are directed to the appropriate data sources or prompts. Logical routing uses LLM reasoning to classify and route questions, while semantic routing relies on embedding and similarity computation. Both methods can be tailored to specific domains and use cases, enhancing the retrieval process.

Next readme will explore about query structing to filter chunks.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!