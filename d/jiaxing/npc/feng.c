// npc: /d/xingxiu/npc/ke.c
// by shang  97/6

inherit NPC;

void create()
{
        set_name("ŷ����", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "�����ǡ���������ŷ���档\n" "����������ǰ�ļ�������֮�ϣ�����ί�٣�����΢����\n");
        set("title", "�϶���");
        set("gender", "����");
        set("age", 53);

        set("attitude", "peaceful");

        set("str", 30);
        set("int", 24);
        set("con", 30);
        set("dex", 24);

        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 200);
        set("max_neili", 1500);
        set("jiali", 50);

        set("combat_exp", 1500000);
        set("score", 200000);
        set_skill("force", 200);

   // other set needed for future use.

        setup();
}
