# RAG from Scratch: Part 11 - Query Structuring

Welcome to the 11th part of our RAG from scratch series focused on query structuring.

## Introduction to Query Structuring

We've previously discussed query translation, which involves converting a question into a form optimized for retrieval, and routing, which involves directing the question to the appropriate data source. Now, we'll talk about query structuring, which is the process of converting natural language into a domain-specific language for querying different sources.

![query-construction](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/query-construction.png)

## Problem Statement

Imagine we have an index of LangChain video transcripts. You might want to ask a question like, "Find me videos on ChatLangChain published after 2024." Query structuring converts this natural language question into a structured query that can be applied to metadata filters on your vector store.

![query-structuring-metadata-filters](https://github.com/DharaniDJ/My-Programming-Journey/blob/assets/assets/RAG/query-structuring-metadata-filters.png)

## Approach

To achieve this, we'll use function calling. We'll provide the metadata fields present in our vector store to the model, which will then produce queries adhering to the schema provided. These queries can then be parsed into a structured object, such as a Pydantic object, which can be used in search.

### Example Metadata Fields

- Description
- URL
- Publish Date
- Length

### Example Filters

- Range filtering on view count, publication date, video length
- Unstructured search on contents and title


## Implementation in Code

Many vectorstores contain metadata fields.

This makes it possible to filter for specific chunks based on metadata.

Let's look at some example metadata we might see in a database of YouTube transcripts.

### Step-by-Step Code Walkthrough

```python
from langchain_community.document_loaders import YoutubeLoader

docs = YoutubeLoader.from_youtube_url(
    "https://www.youtube.com/watch?v=pbAd8O1Lvm4", add_video_info=True
).load()

docs[0].metadata
```

{'source': 'pbAd8O1Lvm4',
 'title': 'Self-reflective RAG with LangGraph: Self-RAG and CRAG',
 'description': 'Unknown',
 'view_count': 11922,
 'thumbnail_url': 'https://i.ytimg.com/vi/pbAd8O1Lvm4/hq720.jpg',
 'publish_date': '2024-02-07 00:00:00',
 'length': 1058,
 'author': 'LangChain'}

Let’s assume we’ve built an index that:

Allows us to perform unstructured search over the contents and title of each document
And to use range filtering on view count, publication date, and length.
We want to convert natural langugae into structured search queries.

We can define a schema for structured search queries.

```python
import datetime
from typing import Literal, Optional, Tuple
from langchain_core.pydantic_v1 import BaseModel, Field

class TutorialSearch(BaseModel):
    """Search over a database of tutorial videos about a software library."""

    content_search: str = Field(
        ...,
        description="Similarity search query applied to video transcripts.",
    )
    title_search: str = Field(
        ...,
        description=(
            "Alternate version of the content search query to apply to video titles. "
            "Should be succinct and only include key words that could be in a video "
            "title."
        ),
    )
    min_view_count: Optional[int] = Field(
        None,
        description="Minimum view count filter, inclusive. Only use if explicitly specified.",
    )
    max_view_count: Optional[int] = Field(
        None,
        description="Maximum view count filter, exclusive. Only use if explicitly specified.",
    )
    earliest_publish_date: Optional[datetime.date] = Field(
        None,
        description="Earliest publish date filter, inclusive. Only use if explicitly specified.",
    )
    latest_publish_date: Optional[datetime.date] = Field(
        None,
        description="Latest publish date filter, exclusive. Only use if explicitly specified.",
    )
    min_length_sec: Optional[int] = Field(
        None,
        description="Minimum video length in seconds, inclusive. Only use if explicitly specified.",
    )
    max_length_sec: Optional[int] = Field(
        None,
        description="Maximum video length in seconds, exclusive. Only use if explicitly specified.",
    )

    def pretty_print(self) -> None:
        for field in self.__fields__:
            if getattr(self, field) is not None and getattr(self, field) != getattr(
                self.__fields__[field], "default", None
            ):
                print(f"{field}: {getattr(self, field)}")
```
Now, we prompt the LLM to produce queries

```python
from langchain_core.prompts import ChatPromptTemplate
from langchain_openai import ChatOpenAI

system = """You are an expert at converting user questions into database queries. \
You have access to a database of tutorial videos about a software library for building LLM-powered applications. \
Given a question, return a database query optimized to retrieve the most relevant results.

If there are acronyms or words you are not familiar with, do not try to rephrase them."""
prompt = ChatPromptTemplate.from_messages(
    [
        ("system", system),
        ("human", "{question}"),
    ]
)
llm = ChatOpenAI(model="gpt-3.5-turbo-0125", temperature=0)
structured_llm = llm.with_structured_output(TutorialSearch)
query_analyzer = prompt | structured_llm
```

```python
query_analyzer.invoke({"question": "rag from scratch"}).pretty_print()
```
content_search: rag from scratch
title_search: rag from scratch

```python
query_analyzer.invoke(
    {"question": "videos on chat langchain published in 2023"}
).pretty_print()
```
content_search: chat langchain
title_search: 2023
earliest_publish_date: 2023-01-01
latest_publish_date: 2024-01-01

```python
query_analyzer.invoke(
    {"question": "videos that are focused on the topic of chat langchain that are published before 2024"}
).pretty_print()
```
content_search: chat langchain
title_search: chat langchain
earliest_publish_date: 2024-01-01

```python
query_analyzer.invoke(
    {
        "question": "how to use multi-modal models in an agent, only videos under 5 minutes"
    }
).pretty_print()
```
content_search: multi-modal models agent
title_search: multi-modal models agent
max_length_sec: 300

To then connect this to various vectorstores, you can follow [here](https://python.langchain.com/docs/how_to/self_query/)

### Example Usage

1. **Semantic Search**: Perform a semantic search based on the content and title.

```python
# Example question
question = "RAG from scratch"

# Generate the structured query
structured_query = bind_to_llm(question)
print(structured_query)
```

2. **Date Filter Search**: Perform a search with a date filter.

```python
# Example question with date filter
question = "Find videos on ChatLangChain published before 2024."

# Generate the structured query
structured_query = bind_to_llm(question)
print(structured_query)
```

### Useful links for reference

- https://blog.langchain.dev/query-construction/
- https://blog.langchain.dev/enhancing-rag-based-applications-accuracy-by-constructing-and-leveraging-knowledge-graphs/
- https://python.langchain.com/docs/tutorials/query_analysis/
- https://python.langchain.com/docs/how_to/self_query/

## Conclusion

Query structuring is a powerful technique for converting natural language questions into structured queries that can be applied to metadata filters on vector stores. This approach leverages function calling to produce queries that adhere to a specific schema, making it easier to perform complex searches. This technique is highly versatile and can be applied to various domains and data sources.

Next readme will explore about indexing particularly multi-representation indexing.

Stay tuned for more in-depth tutorials on RAG!

Thanks for reading!