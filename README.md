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

* Implement resource management mechanism;
* Implement lists on Message;
* Implement addressing on Message;
* Implement the message routing mechanism for JNI;
* Implement the message routing mechanism for thread -> process -> IP;
* Create the concept of runtime;
   * Create the concept of runtime versioning;
* Create the concept of packaging mechanism;
   * Create the concept of loading mechanism;
   * Create the concept of modulee versioning;
   * Create the concept of  module identification (unique naming).
