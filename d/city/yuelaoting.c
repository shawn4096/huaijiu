// /d/city/yuelaoting.c
// update by beyond

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "����ͤ");
	set("long", @LONG
���������ݳǵ�����ͤ��ͤ������������������������Ҳ��Щ����Ф
�񻭣������в������������������ϣ�����Ҹ������ż���м�������
�����ú�ʹ��˳�����ʮ�����ۡ������������ﶼ����������ȥ���Ǽǡ�
LONG
        );

	set("exits", ([
		"west" : __DIR__"yueqidian",
		"north" : __DIR__"yltw",
        ]));
	set("objects",([
		__DIR__"npc/yuelao" : 1,
                __DIR__"npc/shuang" : 1,
        ]));
	set("no_fight", 1);
	set("no_sleep_room", 1);
	set("coor/x",130);
  set("coor/y",-30);
   set("coor/z",0);
   setup();
       call_other("/clone/board/yuelao_b", "???");
}
