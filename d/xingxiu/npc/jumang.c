// animal: snake.c
// Jay 3/18/96

inherit NPC;

void create()
{
        set_name("����", ({ "ju mang" }));
        set("race", "Ұ��");
        set("age", 200);
        set("long", "һ���Ӵ��ޱ�, ɫ�ʰ�쵵ľ����� ������������ǿ�ҵ��ȳ�ζ��\n");
        set("attitude", "peaceful");
        set("str", 70);
        set("con", 50);
        set("max_qi", 800);
        set("limbs", ({ "ͷ��", "����", "β��" }) );
        set("verbs", ({ "bite" }) );
        set("combat_exp", 120000);
        set_temp("apply/attack", 50);
        set_temp("apply/armor", 50);
        setup();
}

void init()
{
    object ob;
    mapping myfam;
    ::init();
    if (interactive(ob = this_player()) && !is_fighting()) {
        myfam = (mapping)ob->query("family");
     if ((!myfam || myfam["family_name"] != "������") &&
          (!wizardp(ob))) {
           remove_call_out("do_killing");
           call_out("do_killing",1,ob);
           }
     }
}