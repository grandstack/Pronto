# Pronto

```cpp
auto main() -> int
{
	using sprite = pronto::entity<position, collision, health, texture>;

	auto a = pronto::create<sprite>(100000);
	auto b = pronto::create<sprite>(100000);

	pronto::process(a, [&](health & h1, collision & c1) {
		pronto::process(b, [&](collision & c2, health & h2) {
			if (c.collide(c1))
			{
				h1.health(h1.health() - 1);
				h2.health(h1.health() - 1);
			}
		});
	});
}
```
