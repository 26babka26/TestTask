# TestTask

## Task 1

1. Первое, что бросилось в глаза `Player*`, ему присваивается `nullptr`, а дальше он нигде не создается и не удаляется. Я бы заменил обычный указатель на `unique_ptr`.

2. В `Client::send` мы обращаемся к приватному полю `io`, без `this`, в остальном коде обращение к приватным полям через `this`.

3. В `Client::login` в хеддере аргументы передается по константной ссылке, в реализации по указателю. 

4. `switch-case` c обработчиками заменил бы на массив `std::function` или на мапу {Тип пакета, Метод} или реализовал бы обработчики разных пакетов используя статический полиморфизм.

```cpp
namespace
{
	using PacketHandler = void (Client::*)(const server::Packet &);

	static constexpr auto make_handlers()
	{
		std::array<PacketHandler, static_cast<int>(server::PacketType::LAST)> handlers{};

		static_assert(
			static_cast<int>(server::PacketType::PARAMS_SET) !=
				static_cast<int>(server::PacketType::BUY) &&
			static_cast<int>(server::PacketType::BUY) != static_cast<int>(server::PacketType::LOGIN));

		handlers[static_cast<size_t>(server::PacketType::PARAMS_SET)] = &Client::handle_params_set;
		handlers[static_cast<size_t>(server::PacketType::BUY)] = &Client::handle_buy;
		handlers[static_cast<size_t>(server::PacketType::LOGIN)] = &Client::login;

		return handlers;
	}
}

...

void Client::on_packet(const server::Packet &packet)
{
	if(packet.get_type() >= server::PacketType::LAST)
		logger->warning("Unhandled packet type {}", packet.get_type());

	std::invoke(this->handlers[packet.get_type()]);
}

```

## Task 2

Для хранения записей в `TopTracker` я использовал `std::deque`. Я посчитал, что операции удаления и добавления будут самыми частыми. Добавление и удаление элемента, если превышено количество записей для хранения происходит за O(1). Удаление просроченных записей происходит за O(`std::distance(begin, last_expired)`). В моем случае контейнер отсортирован, если гарантии отсортированности нет(например, если добавление записей происходит в разных потоках), то стоит поменять:

```cpp
const auto expired_it = std::ranges::lower_bound(this->players_actions.begin(), this->players_actions.end(), expired_time, std::less{}, &PlayerAction::time);
this->players_actions.erase(this->players_actions.begin(), expired_it);
```

на

   ```cpp
const auto [begin, end] = std::ranges::remove_if(this->players_actions, std::bind_front(std::less{}, expired), &PlayerAction::time);
this->players_actions.erase(begin, end);
```

тогда удаление будет O(n). Если код будет использоваться многопоточно, то так же стоило бы защитить операции с контейнером мьютексами.

## Task 3

Делал в OneCompiler используя mySql
