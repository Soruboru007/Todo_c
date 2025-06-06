# Makefile for TODO Console Application

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = todo
OBJS = main.o todo.o
HEADERS = todo.h

# デフォルトターゲット
all: $(TARGET)

# 実行ファイルの生成
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# main.oの生成
main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

# todo.oの生成
todo.o: todo.c $(HEADERS)
	$(CC) $(CFLAGS) -c todo.c

# クリーン（オブジェクトファイルと実行ファイルを削除）
clean:
	rm -f $(OBJS) $(TARGET)

# 完全クリーン（データファイルも削除）
cleanall: clean
	rm -f tasks.dat

# 実行
run: $(TARGET)
	./$(TARGET)

# ヘルプ
help:
	@echo "使用可能なターゲット:"
	@echo "  make         - アプリケーションをビルド"
	@echo "  make run     - アプリケーションを実行"
	@echo "  make clean   - オブジェクトファイルと実行ファイルを削除"
	@echo "  make cleanall- データファイルも含めて削除"
	@echo "  make help    - このヘルプを表示"

.PHONY: all clean cleanall run help