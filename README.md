# Pronto

```cpp
auto main() -> int
{
	using person = pronto::entity<food, hunger>;

	auto bag = pronto::create<person>(1000);

	pronto::process(bag, [&](person & p1, food & f) 
	{
		pronto::process(bag, [&](person & p2, hunger & h) 
		{
			if(p1 != p2) 
			{
				h.eat(f);
			}
		});
	});

	pronto::destroy(bag);
}
```
