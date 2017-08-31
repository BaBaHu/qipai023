/** 
 desc:��ָ���ؼ����� ���������ܣ�
 һ��CCNodeͬʱִ�ж��CCShake����,����һ��CCShakeû������ִ��һ��CCShake�Ļ��ͻ��������,�����ƫ�Ƶ�����! 
  
 �������: 
 1).��Ҫͬʱִ�ж��CCShake����. 
 2.�Լ��ⲿ��¼���CCNode��λ��,ִ����ɺ��ֶ�setPosition(); 
*/
#ifndef __MESHAKE_H__
#define __MESHAKE_H__

#include "cocos2d.h"
USING_NS_CC;

class MEShake : public ActionInterval
{
public:
    MEShake();
    
    // Create the action with a time and a strength (same in x and y)
    // ������Ч���ĳ�ʼ����������,����������ͬ
    // @param d �𶯳�����ʱ��
    // @param strength �𶯵ķ���
    static MEShake* create(float d, float strength);
    // Create the action with a time and strengths (different in x and y)
    // ������Ч���ĳ�ʼ������,��������ֵ��һ��
    static MEShake* create(float d, float strength_x, float strength_y);
    bool initWithDuration(float d, float strength_x, float strength_y);
    
    //���¶�����д���������ĺ���(������д)
    virtual MEShake* clone(void) const override;
    virtual MEShake* reverse(void) const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
    virtual void stop(void);
    
protected:
     // Initial position of the shaked node
     // �����λ��
     float _initial_x, _initial_y;
     // Strength of the action
     // �����ķ���
     float _strength_x, _strength_y;
};

#endif // !__MESHAKE_H__