// /d/xiangyang/cross1.c

inherit ROOM;

void create()
{
        set("short", "丁字路口");
        set("long", @LONG
这里是军事重镇襄阳城中通往北门和西门的丁字路口，不时地有顶盔贯甲
的士兵走来走去。向北出城可以进入陕西、河南境内，还能去参观著名的武当
山。东面隐约有一家小药铺。
LONG
        );
        set("outdoors", "襄阳");

        set("exits", ([
                "west" : __DIR__"bhnj",
                "north" : __DIR__"nroad1",
                "east" : __DIR__"yaopu",
                "south" : __DIR__"cross2",
        ]));
        setup();
}

