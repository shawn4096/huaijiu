// Room: /d/wizard/wizard_room.c

inherit ROOM;

void create()
{
        set("short", "��ʦ������");
        set("long", @LONG
�ڿ������Ĵ����������з���һ�ź�ľ��Բ������ʦͨ��������
������ͨ��һЩ��Ҫ������޸ĵ��᰸�����������԰��ܻ㣬�ϱ��Ͷ��ߵ�
ͨ����ͨ��������̨�������ͨ��ͨ���Խ�ɽׯ�����ҡ�
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"wizard_room",
                "tiandi" : "/cmds/leitai/leitai",
                "fengyun" : "/cmds/leitai/leitai1",
                "longhu" : "/cmds/leitai/leitai2",
                "up" : "/cmds/leitai/bwdh/ctrl",
        ]));
        set("valid_startroom", 1);
        set("no_fight", 1);
        set("coor/x",10);
  set("coor/y",0);
   set("coor/z",9999);
   setup();

        call_other("/clone/board/post_b", "???");
}
void init()
{
  	object ob = this_player();

  	if (userp(ob) && !wiz_level(ob)) {
    		ob->move("/d/wizard/guest_room");
    		message_vision("$N����ʦ��Ϣ�����ص�ˤ��������\n", ob);
    		ob->unconcious();
  	}
}



