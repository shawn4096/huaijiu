// /d/wudang/xuanyuemen.c ������
// by ydh and shang

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����ǰ���������������䵱ɽ������һ����ľ��ï�ĸ�ɽ������
ɽ�屻�������֣��Ѽ�ȫò��һ��ʯ���������ϣ���Լ�ɼ���������͡�
һ������ʯ��(fang)��ɽ�������䵱ɽ����̫��ɽ��Ϊ��ʮ������֮һ��
�ж�ʮ�߷塢��ʮ���ҡ���ʮ�Ľ�����̨���微����̶�������š�����
���һ���أ�����������ɭ�ޣ����ղ��죬�����ľ�����������������
����ӭ�����͵ĵ�һվ��
LONG
        );
        set("exits", ([
                "east" : __DIR__"wdroad8",
                "west" : __DIR__"yaofang.c",
                "southup" :__DIR__"shijie1",
        ]));

        set("item_desc", ([
                "fang" : RED "�䵱ɽ\n"NOR,
        ]));

        set("no_clean_up", 0);

        set("coor/x",20);
  set("coor/y",30);
   set("coor/z",0);
   setup();

}

int valid_leave(object me, string dir)
{
	if (dir == "southup" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
