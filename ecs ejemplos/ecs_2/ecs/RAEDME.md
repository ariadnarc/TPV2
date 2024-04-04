# Entity-Component-System v2

This version implements only Entity-Component. Components inherit from the class Component, Entity maintains an array with a fixed number of (possible) components, and Manager maintains a list of entities. 

It also support groups of entities and handlers (assigning identifiers to entities for fast global access). However, unlike v1, in this version each entity belongs to a single group, resulting in a more efficient implementation. Entities keep no information on groups, everything is done in the manager.

