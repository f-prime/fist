# Spear

Spear is a simple lightweight in memory key value store. It supports key-value lookup, lists, and full-text search. Spear is meant to be a simple but powerful tool that does a few things very well and works best when paired with another database engine such as MongoDB or Postgres, though it can also standalone.

Spear also reliabily persists data to the disk as it receives it making it useful for more traditional database applications, though this is not the main focus. 

Some usecase include:

- Caching
- Web page indexing
- Light weight user database
- Session key management

*Spear is still under development and not all the above features are yet implemented or stable.* 

# Build

```
make build
./bin/spear
```

# Examples

### Hashmap

```
spear> set project "Spear Project"
spear> get project
"Spear Project"
```

### Lists

```
spear> ladd features "Full text search","hashmap","lists"
spear> lget features
["Full text search", "hashmap", "lists"]
```

### Full-Text Search

```
spear> index "25" "Some text to index"
spear> search "Some text"
"25"
```

# Key Features

- In memory key-value store
- Full text indexing and searching
- Lists
- Persisting data to disk
