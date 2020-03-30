#ifndef RESULT_HPP
#define RESULT_HPP

template <typename T>
class Result {
public:
  Result(bool handled, void* handler = nullptr)
      : handled_(handled),
        handler_(handler) {}

private:
  bool  handled_;
  void* handler_;

};


#endif // RESULT_HPP

