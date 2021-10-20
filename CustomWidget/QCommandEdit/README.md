# QCommandEdit

A Qt widget, subclass of QLineEdit, for entering commands, with features common in modern shells such as TAB-completion, history, history-search.

Demo application included.

Use the widget just like a `QLineEdit` widget.

![Screenshot](QCommandEdit.gif)

Signals:

 - `execute(const QString &cmd)` emitted when Return is pressed with some text typed in;
 - `askCompletion(const QString &cmd, int cursorPos)` emitted when Tab is pressed;
 - `escape()` emitted when Esc is pressed and the field is empty.

Slots:

 - `setHistory(const QStringList &history)` for setting the history (the history is not managed by the widget, it must be maintained by the host application, e.g.: in reaction to the `execute(const QString &cmd)` signal, the command is executed, it is also appended to the history list, and `setHistory(const QStringList &history)` is called to sync the widget's history);
 - `setCompletion(const QStringList &completion)` for setting the list of completion (in reaction to `askCompletion(const QString &cmd, int cursorPos)` signal);
 - `acceptCompletion()` accepts the current completion (selected text); bound to Return key;
 - `cancelCompletion()` discards the current completion (selected text); bound to Esc key;
 - `setToolTipAtCursor(const QString &tip)` show a tooltip placed at cursor position (useful for implementing calltips).

## Contribute

If you want to contribute with development, fork and make a pull requests. PRs are very welcome!

If you want to donate, use one of the following methods:

 - BTC: `34RqXSKCgPrVJ8Q266ahiWx3TfV2xAdNKv`
 - BCH: `1PwoEfCk7cjjYiC3B9y5JQkCAtZsaZwfxn`
 - ETH: `0x3a1Fe92C19609835De3975F64fca4c4aA9B0BDf3`
 - LTC: `LYTUr4xiMjwii88J8sZ44wWu8GCaCQVx3W `
 - XMR: `4GdoN7NCTi8a5gZug7PrwZNKjvHFmKeV11L6pNJPgj5QNEHsN6eeX3DaAQFwZ1ufD4LYCZKArktt113W7QjWvQ7CWCSnRSymAvuG1vvpqi`
