
inherit ROOM;

void create()
{
        set("short", "�ɿ�");
        set("long",
"��ӭ�����󺣷������˶ɿڣ�������һ����ģ����Ķɿڡ�
���ڳ�͢�������������ٵĶɿڽ�����˥���ˡ�\n"
        );
	set("outdoors", "��ɽ");
	set("no_fight",1);
	set("exits",([
        "northwest" : __DIR__"shulin1",
]));
        set("objects", ([
        __DIR__"npc/chuanlaoda" : 1,
]));
	set("coor/x",30);
        set("coor/y",-550);
        set("coor/z",0);

	setup();
}
