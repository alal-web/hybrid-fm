# HybridFM

Гибридный файловый менеджер и веб-браузер на базе Qt5 и KDE Frameworks.

## О проекте

HybridFM объединяет файловый менеджер и полнофункциональный веб-браузер в одном приложении. Поддерживает вкладки, закладки, плагины и интеграцию с окружением KDE через KIO и D-Bus.

**Для кого:** пользователи AstraLinux, которым нужен объединённый файловый и веб-браузер, или кто ищёт лёгкий Qt-based файловый менеджер с встроенным веб-браузером

## Технологии

|  | Технология |
|---|---|
| Язык | C++17 |
| UI-фреймворк | Qt 5.15+ |
| KDE-интеграция | KF5 (Parts, KCMUtils, KIO, Crash, WindowSystem) |
| Веб-движок | QtWebEngine (на основе Chromium) |
| Проверка правописания | Hunspell |
| Сборка | CMake 3.16+ |
| Лицензия | GPL v2 |

## Сборка

**Зависимости:** Qt 5.15+, KDE Frameworks 5.91+, CMake 3.16+, Hunspell.

Установка зависемостей с помощью apt:
```bash
./install-deps.py
```

Сборка:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```


## Запуск

```bash
./build/bin/hybrid-fm
```

Настройки хранятся в `~/.config/hybrid-fmrc`.

## Структура проекта

- `src/` — основное приложение (окно, вкладки, сессии, история)
- `libkonq/` — ядро (провайдер истории, popup-меню, события)
- `sidebar/` — модули боковой панели (закладки, история, places, дерево)
- `webenginepart/` — интеграция с QtWebEngine
- `settings/` — страницы настроек
- `plugins/` — плагины (kget, shellcmd, babelfish и др.)
- `client/` — поддержка протокола KFMClient
- `autotests/` — юнит-тесты

