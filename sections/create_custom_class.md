## 🏛 Create custom class

<table><tr><td>
This section was NOT written in conjunction with ChatGPT.
</td></tr></table>

<figure>
    <img src="static/img/ActorLifeCycle.png" alt="Lifecycle breakdown" />
    <figcaption>Lifecycle breakdown</figcaption>
</figure>

You can read more about [actor's lifecycle at Unreal's docs](https://docs.unrealengine.com/5.3/en-US/unreal-engine-actor-lifecycle/).

By inheriting from `AActor` class:

```cpp
void PostInitComponents();
void BeginPlay(); // Can be called multiple times
void Tick(float DeltaTime);
void EndPlay();
```
