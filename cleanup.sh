#!/usr/bin/env bash
set -euo pipefail

TARGET_DIR="${1:-.}"

echo "目標資料夾：$TARGET_DIR"
echo "以下是將會刪除的項目："
echo

find "$TARGET_DIR" \
  \( -name ".DS_Store" -type f \
  -o -name "*.pyc" -type f \
  -o -name "__pycache__" -type d \
  -o -name ".pytest_cache" -type d \
  -o -name ".mypy_cache" -type d \
  -o -name ".ruff_cache" -type d \
  -o -name ".venv" -type d \
  -o -name "venv" -type d \
  -o -name "node_modules" -type d \) \
  -print

echo
read -r -p "確定要刪除以上項目嗎？輸入 yes 才會繼續： " CONFIRM

if [ "$CONFIRM" != "yes" ]; then
  echo "已取消。"
  exit 0
fi

echo "開始刪除..."

find "$TARGET_DIR" -name ".DS_Store" -type f -delete
find "$TARGET_DIR" -name "*.pyc" -type f -delete

find "$TARGET_DIR" -name "__pycache__" -type d -prune -exec rm -rf {} +
find "$TARGET_DIR" -name ".pytest_cache" -type d -prune -exec rm -rf {} +
find "$TARGET_DIR" -name ".mypy_cache" -type d -prune -exec rm -rf {} +
find "$TARGET_DIR" -name ".ruff_cache" -type d -prune -exec rm -rf {} +

find "$TARGET_DIR" -name ".venv" -type d -prune -exec rm -rf {} +
find "$TARGET_DIR" -name "venv" -type d -prune -exec rm -rf {} +

find "$TARGET_DIR" -name "node_modules" -type d -prune -exec rm -rf {} +

echo "清理完成！"
