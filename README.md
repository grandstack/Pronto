# Pronto

```cpp
auto main() -> int
{
	using person = pronto::entity<food, hunger>;

	auto bag = pronto::create<person>(1000);

	pronto::process(bag, [&](person & p, food & f) {
		std::cout << "id: " << p << std::endl;

		pronto::process(bag, [&](hunger & h) {
			h.eat(f);
		});
	});

	pronto::destroy(bag);
}
```
