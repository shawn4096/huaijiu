// Room: /d/xianyang/xiaocd.c

inherit ROOM;

void create()
{
        set("short", "客来小吃店");
        set("long", @LONG
这是一家生意兴隆的小吃店，人来人往很是热闹，为数不多的长条板凳上
都坐得满满的，还有些过路人站在外面等着。角落里有几个江湖豪客在大声谈
论着什么，好象是最近武林的传闻。
LONG
        );

        set("exits", ([
                "south" : __DIR__"bhnj",
        ]));

        set("objects", ([
                __DIR__"npc/waiter" : 1,
                "/d/huashan/npc/haoke":2,
        ]));

        setup();
}

