#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <set>
#include <string>
#include <utility>

class Folder;

class Message {
  std::string m_contents;
  std::set<Folder *> m_folders;

  void addToAll();
  void removeFromAll();
  void moveFolders(Message &);

 public:
  explicit Message(std::string contents) : m_contents{std::move(contents)} {}
  Message(const Message &other)
      : m_contents{other.m_contents}, m_folders{other.m_folders} {
    addToAll();
  }
  Message(Message &&other) : m_contents{std::move(other.m_contents)} {
    moveFolders(other);
  }
  Message &operator=(const Message &other) {
    removeFromAll();
    m_contents = other.m_contents;
    m_folders = other.m_folders;
    addToAll();
    return *this;
  }
  Message &operator=(Message &&other) {
    if (this != &other) {
      removeFromAll();
      m_contents = std::move(other.m_contents);
      moveFolders(other);
    }
    return *this;
  }
  ~Message() {
    removeFromAll();
  }

  void addFolder(Folder &folder) {
    m_folders.insert(&folder);
  }
  void removeFolder(Folder &folder) {
    m_folders.erase(&folder);
  }
};

class Folder {
  std::set<Message *> m_messages;

 public:
  void addMessage(Message &msg) {
    m_messages.insert(&msg);
  }
  void removeMessage(Message &msg) {
    m_messages.erase(&msg);
  }
};

void Message::addToAll() {
  for (auto f : m_folders)
    f->addMessage(*this);
}

void Message::removeFromAll() {
  for (auto f : m_folders)
    f->removeMessage(*this);
}

void Message::moveFolders(Message &other) {
  other.removeFromAll();
  m_folders = std::move(other.m_folders);
  addToAll();
}

#endif // MESSAGE_HPP