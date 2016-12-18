# Veritas Orchestra

Veritas Orchestra is an (in-development) easily integrable (principle 1.) module system that abstracts processing context (principle 2.) and implements a messaging mechanism which makes it perfect for building modular (heh) distributed systems.

# Usage example

https://www.github.com/Silexars/VeritasFileSystem

# Implemented features

* API for modules;
   * Module interfacing;
   * Module messaging;

# Principles

1. Make it easily integrable with any programming paradigm;
2. Don't worry about module processing context (e.g. thread, process, local, remote);
3. Make modules easily redistributable;
4. Ontologic minimalism.

# Roadmap

### Core

* Implement lists on Message;
* Implement addressing on Message;
* Implement protocol-agnostic message routing mechanism;

### Extensions

* Implement message routing for JNI;
* Implement message routing for thread;
* Implement message routing for process;
* Implement message routing for IP;

### Utils

* Implement resource management mechanism;

### Design

* Create the concept of runtime;
   * Create the concept of runtime versioning;
* Create the concept of packaging mechanism;
   * Create the concept of loading mechanism;
   * Create the concept of module versioning;
   * Create the concept of  module identification (unique naming).
