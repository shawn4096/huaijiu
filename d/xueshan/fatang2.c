// Room: fatang2.c

inherit ROOM;

void create()
{
	set("short", "���ö�¥");
	set("long", @LONG
�����Ǵ��������ž������������ģ�����֤������������ǣ�
    Ϸ������ɽǰ�£��������������ӡ�
    ��Ȼ���������д�һ¥�㡣
    �����⣬Ⱥɽ���֣�������ء�
    �����⣬¥̨���䣬�������С�
LONG
	);

	set("exits", (["down" : __DIR__"fatang",]));
        set("objects", ([CLASS_D("xueshan") + "/jiumozhi" : 1,]));
	setup();
}
