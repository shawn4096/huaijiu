inherit ROOM;

void create()
{
        set("short", "仰魁");
        set("long", @LONG
        [1;33m》》》》》》》》》》》》》》》》》》》》[0m
            [1;33m》》[0m                                [1;33m》》[0m
            [1;33m》》[0m 　[1;33;41m弘[0m    [1;33;41m幎[0m　　[1;33;41m逸[0m　　[1;33;41m悳[0m   [1;33;41m倶[0m  [1;33m  》》[0m
            [1;33m》》[0m                                [1;33m》》[0m
            [1;33m》》》》》》》》》》》》》》》》》》》》[0m

    宸戦嗤膨訳恠脆宥�魏四�議弘幎型寂。型寂戦中菊諮宥苧��喟垓彈姥
彭葎弘幎髄断捲暦。能貧薮彭匯嫖窟仔議崕(paper)��貧中亟彭弘幎壇議
雫艶。低辛參臥心光弘幎型(pigroom)議繁方彜趨。
LONG
        );
        
        set("item_desc", ([
                "paper" : 
"‐弘幎逸／議雫艶喇詰欺互蛍葎��\n\n"
"仟返��僥湧��湧伏��慕伏��倔嘉��\n"
"訟繁��盾圷��恒平��氏圷��序平��\n"
"放耳平��勧詬��冥雑��茨凛��彜圷��\n"
"魂爽��僥平��寄僥平��遍絹��糟倪��\n"
"寄忱弗��逸麼\n"
        ]));
        
        set("exits", ([
        "east" : __DIR__"eproom",
        "west" : __DIR__"wproom",
        "south" : __DIR__"sproom",
        "north" : __DIR__"nproom",
        "down" : __DIR__"duchang",
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("objects", ([
               __DIR__"npc/qian-laoben" : 1,
        ]));

        set("coor/x",90);
  set("coor/y",-20);
   set("coor/z",10);
   setup();
        "/clone/board/pig_b"->foo();
}


void init()
{
    add_action("do_pigroom", "room");
    add_action("do_pigroom", "pigroom");
}

int do_pigroom()
{
	object env1, env2, env3, env4;
    object *obj1, *obj2, *obj3, *obj4;
    object me = this_player();
    int i, i1, i2, i3, i4;

	env1 = load_object(__DIR__"eproom.c");
	obj1 = all_inventory(env1);

	env2 = load_object(__DIR__"nproom.c");
	obj2 = all_inventory(env2);

	env3 = load_object(__DIR__"sproom.c");
	obj3 = all_inventory(env3);

	env4 = load_object(__DIR__"wproom.c");
	obj4 = all_inventory(env4);


    for (i = 0; i < sizeof(obj1); i++) 
        if (userp(obj1[i]))
            i1++;

    for (i = 0; i < sizeof(obj2); i++) 
        if (userp(obj2[i]))
            i2++;

    for (i = 0; i < sizeof(obj3); i++) 
        if (userp(obj3[i]))
            i3++;

    for (i = 0; i < sizeof(obj4); i++) 
        if (userp(obj4[i]))
            i4++;

        tell_object(me, "�嶬攜�弘幎型戦議繁方嗤��\n" + 
        "　　　　臼" + "\n" +
        "　　　　" + i2 + "\n" +
        "　廉 " + i4 + "　　　" + i1 + " 叫\n" + 
        "　　　　" + i3 + "\n" +
        "　　　　掴 \n");
    return 1;
}

