#ifndef _ALARM_H_
#define _ALARM_H_

#include <cstring>
typedef unsigned short word;

class Alarm
{
    private:
        const int _stackSize;
        int index;
        
        struct AlarmStack
		{
			int type; 	
			int no;
			char message[256];
		}*_alarmStack;

        struct AlarmType
        {
            enum Type
            {
                fault,
                warning,
                debug
            };
        }_AlarmType;

    public:
        Alarm():
            _stackSize(5)
        {
            _alarmStack = new AlarmStack[_stackSize];
        }

        Alarm(
            int stack
        ):
            _stackSize(stack)
        {
            _alarmStack = new AlarmStack[_stackSize];
        }

        ~Alarm()
        {
            delete _alarmStack;
		}

		void SetFault(int no, char* message = "")
		{
			_alarmStack[index].type = _AlarmType.fault;
			SetAlarm(no, message);
		}
        void SetWarning(int no, char* message = "")
        {
            _alarmStack[index].type = _AlarmType.warning;
            SetAlarm(no, message);
        }

        void SetDebug(int no, char* message = "")
        {
            _alarmStack[index].type = _AlarmType.debug;
            SetAlarm(no, message);
        }

        void GetAlarm(int& type, int& no, char* message)
        {
			int tmpIndex = (index == 0 ? _stackSize : index - 1);
            type    = _alarmStack[tmpIndex].type;
            no      = _alarmStack[tmpIndex].no;
            strcpy(message, _alarmStack[tmpIndex].message);
        }

    private:
        void SetAlarm(int no, char* message)
        {
            _alarmStack[index].no        = no;
            strcpy(_alarmStack[index].message, message);
            index >= _stackSize ? index = 0 : index++;
        }

};
#endif //_ALARM_H_