// by Xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "������ԭ");
	set("long", @LONG
�ƺ���һ�����н�������ԭ�п���������СϪ���д�����ɳ�����
�ӣ��γ�ǧ�����֡�����֮���һ���ƽ�ؽ���̨ܫ���ƺ����ɹŸ�ԭ
�ϱ������ʣ���̫��ɽ������������תͷ���£��γɽ��µķֽ硣
LONG );
	set("exits", ([
		"northeast" : __DIR__"hetao",
		"southwest" : __DIR__"huanghe_2",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",100);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

