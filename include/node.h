#include "value.h"
#include <cstdint>
#include <vector>

#ifndef NODE_H
#define NODE_H

using namespace std;

class Sendable {
private:
  vector<value> outputs; // 출력들. 서로 다른 크기의 입력들이 가능하다. 
  vector<uint8_t> outputSizes; // 출력될 크기들. 
public:
  vector<uint8_t> getOutputSizes() = 0;
  vector<node *> nextNodes;
  virtual void propagate(); // 혹여나 오버라이딩이 완전히 필요 없다면 virtual을 지울 것. 
};
//TODO propagete 구현 

class IReciveable {
private:
  vector<value> inputs; // 입력들
  vector<uint8_t> inputSizes;
public:
  vector<uint8_t> getInputSizes() = 0;
  virtual void setInputs() = 0; //setter를 이용하는 것보다 inputs를 바꿀 수 있는 더 좋은 방법이 있으면 수정할 것. 
};
//이게 인터페이스여야 할까?

class AbstractNode {
private:
  vector<setting> settings; //TODO setting이라는 구조체를 만들것
public:
  virtual void calculate() = 0;
};

 
class AbstractGate : Sendable, IReciveable, AbstractNode {
// TODO 여기에 채울 것이 있으면 채워넣을것. 
};

/*****************
* 새로운 노드(게이트) 만드는 법
*
* AbstractNode(AbstractGate)를 구현한다. 노드를 만들 경우 입출력이 필요하다면 Sendable과 IRecievable을 구현한다.
* 생성자는 아무 것도 받지 않아야 하며, settings를 이용해 각종 멤버 변수를 채워 넣어야 한다.
* calculate는 실질적인 계산부이며, 모든 노드마다 다르다.
*****************/

/*****************
* TODO Simulator 등의 이름을 가진 '시뮬레이션 제어 클래스'가 필요하다.
* 그 클래스는 AbstractNode의 배열/벡터를 가지고 있으며, Sendable의 propagate 메서드를 호출하고, 그 결과에 따라 
* 목적 노드의 inputs 값을 수정한다. 하지만 해당 출력의 크기와 입력하는 곳의 크기가 다르면 에러가 생겨야 한다.
* 출력의 크기/입력의 크기는 실제 전파가 일어나기 전에도 알 수 있어야 한다. 이는 Simulator 클래스의 메서드로
* 구현될 수 있다. 
*****************/

#endif;
