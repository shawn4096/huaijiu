// by XiaoYao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���������Ĺ�����������פ���ر�����¥�ߴ����ɣ��ſ�������
�ٱ�����������̲�������ˣ����ſڵĸ�ʾ�ϻ������ͨ���Ľ����
����ͼ�Σ�����ͷ����ȥ��ͦ���֡����Ͼ���ȥ���ǵķ����ˣ�������
��������ɽ����
LONG );
	set("exits", ([
		"southeast" : __DIR__"wuqiao",
		"north"     : __DIR__"tumenzi",
	]));
	set("objects", ([
		__DIR__"npc/xixiabing" : 3,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",60);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

