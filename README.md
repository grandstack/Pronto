# Pronto

```cpp
auto main() -> int
{
	using person = pronto::entity<food, hunger, human>;
	using bulldog = pronto::entity<food, hunger, dog>;

	// Synchronization for concurrent read and write attempts ...
	pronto::synchronize<person, dog>([]
	{
		auto people = pronto::create<person>(1000);
		auto bulldogs = pronto::create<bulldog>(1000);

		pronto::process(people, [&](person & p, food & f) {
			std::cout << "entity id: " << p << std::endl;

			pronto::process(bulldogs, [&](hunger & h) {
				h.eat(f)
			});
		});

		pronto::destroy(bag);
	});
}
```
