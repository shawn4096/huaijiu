// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺ�");
	set("long", @LONG
�ƺӳ����ຣ��������֮�����ܵ�������ԭ���赲��ת����
����ȥ��������������ԭ�Ĺ�������ɳ����������ˮɫ�λƣ��ͱ���Ϊ
�ƺӡ�
LONG );
	set("exits", ([
		"west"      : __DIR__"huanghe_3",
		"northeast" : __DIR__"huangtu",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",90);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

