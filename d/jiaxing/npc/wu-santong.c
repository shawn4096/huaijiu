// wu-santong.c ����ͨ
// by shang 97/6

inherit NPC;

void create()
{
        set_name("����ͨ", ({ "wu santong", "wu" }) );
	set("gender", "����" );
        set("age", 45);
	set("long",
"������ͷ�ҷ�������Ҳ��������������һ��,\n" "�뷢�͹��ںڣ���˵��Ͳ��󣬿��������������ݣ�ȴ���߰�ʮ�����̣�\n" "������ֱ׺�����й�����Ӥ�����õĽ���Χ�ѣ�Χ������������è�˵�ͼ����Ȼ�¾����á�\n");
	set("attitude", "friendly");
        set("str", 30);
        set("dex", 24);
        set("con", 30);
        set("int", 20);
        set("shen_type", 1);

        set_skill("unarmed", 120);
        set_skill("force", 120);
        set_skill("dodge", 120);
        set("jiali", 100);

        set("combat_exp", 500000);

        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("max_jingli", 1000);

        set("inquiry", ([
            "�����" : "���䣬�����常Ҳ�����ˣ�",
            "½չԪ" : "���úã����úã�ֻ��ϧ�Ҳ�������ȡ��������",
            "�����" : "�����Ҵ���ӡ�",
            "������" : "�����Ҷ����ӡ�",
            "������" : "�������Ÿ�ʲô��",
       ]) );
	setup();
        carry_object("/d/city/obj/cloth")->wear();
}
