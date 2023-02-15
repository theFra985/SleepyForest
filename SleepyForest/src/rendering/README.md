World objects are split into three types

- Tiles
    - A tile is a static world object. Can be of different sizes that must always be aligned with the world grid.

      [*In case the object has to be offset from the grid a padding can be applied but will be accounted as part of that
      tile size.*]

    - A tile can't be interacted with
    - A tile can't have any special visual effect **outside** it's borders
    - A tile can be defined as a light source
    - A tile can be animated
    - A tile can have an inventory
- Tile entities
    - A tile entity is a dynamic world object.
      The tile entity is a static entity defined as an object offset from a source tile.
      The offset can be defined as a simple cartesian origin offset or as a rotation.
      [The offset can be defined freely from any point of the source tile **(???)** ]
    - A tile entity can be interacted with
    - A tile entity can have special visual effects outside it's borders
    - A tile entity can be defined as a light source
    - A tile entity can be animated
    - A tile entity can have an inventory
- Entity
    - A

Tiles are stored in the grid and are handled as a single layer of the size of the available world map.
Tiles can overlap and overlapping tiles will be rendered in the order in which they are stored (first on the bottom).

Tile entities are stored in the grid and are handled together with the normal tiles.
A tile entity will be registered in all the relevant chunks of the world (defined by it's position and size)
and loaded even if it's source is out of bounds.




> Trees are defined as roots, trunk and leaves.
> The roots are the source tile of the trunk tile entity.
> 
> The leaves are a "feature" that will be rendered only in the first third of the screen??? (And maybe shadow the area a bit when you go under and they disappear?)