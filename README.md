# Pronto

```cpp
auto main() -> int
{
	using person = pronto::entity<food, hunger>;

	auto bag = pronto::create<person>(1000);

	pronto::process(bag, [&](person & one, food & f) {
		std::cout << "id: " << one << std::endl;

		pronto::process(bag, [&](person & two, hunger & h) {
			if(one != two)
			{
				h.eat(f);
			}
		});
	});

	pronto::destroy(bag);
}
```
