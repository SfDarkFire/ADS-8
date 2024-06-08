// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  countOp = 0;
  first = nullptr;
}

void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  if (first == nullptr) {
    first = newCage;
    newCage->next = newCage;  // зацикливаем первый вагон на себя
    newCage->prev = newCage;
  } else {
    Cage* last = first->prev; // находим последний вагон
    last->next = newCage;
    newCage->prev = last;
    newCage->next = first;  // (замыкаем поезд по окружности)
    first->prev = newCage;  // обновляем указатель prev у первого вагона
  }
}

int Train::getLength() {
  first->light = true;
  Cage* first_copy = first;
  int cages = 0;
  while (first->light) {
    cages = 1;
    first_copy = first->next;
    while (!first_copy->light) {
      first_copy = first_copy->next;
      cages += 1;
    }
    first_copy->light = false;
    countOp += 2 * cages;
  }
  return cages;
}

int Train::getOpCount() {
  return countOp;
}
