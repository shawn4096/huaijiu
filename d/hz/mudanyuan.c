// /u/beyond/hangzhou/hongyuchi.c ĵ��԰
inherit ROOM;
void create()
{
        set("short", "ĵ��԰");
        set("long", @LONG
���ߵ�ĵ��԰�ڣ�������ɽ�ߴ���һ���ܰ˽ǵ�ĵ��ͤ��ͤ��ֲ�и���
�����ĵ�������꣬�����ļ�Ӧʱ֮�����˽ڳ���֮�����еİ�Ȼͦ������
���������ˣ�Զ������һ��������й�ɽˮ����
LONG
        );
set("objects",([
__DIR__"npc/you1" : 2,
]));
        set("exits", ([
        "east" : __DIR__"hggyu",
]));
        setup();
}
