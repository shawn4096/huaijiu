// by XiaoYao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
��������Ӫ��ˮ�����ϣ�ƽʱ�˼���������Ϊ����ɳĮ�ﳤ��һ
�������ҩ��----"����"����������˵����ҩ���ܽ�ٶ�������ż��
���������ֲݣ�����ɳĮ�ﳣ�ж����û����ΪΣ�ա�
LONG );
	set("exits", ([
		"southwest" : __DIR__"shixiazi",
		"northeast" : __DIR__"yinpanshui",
	]));
	set("objects", ([
		__DIR__"npc/wugong" : 1,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",80);
  set("coor/y",150);
   set("coor/z",0);
   setup();
}

