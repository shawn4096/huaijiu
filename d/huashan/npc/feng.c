// NPC: /d/huashan/npc/feng.c
// Date: Look 99/03/25

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("������", ( {"feng qingyang","feng","qingyang"} ) );
        set("long", "һλ���������������ֽ�����ߡ�\n" );
        create_family("��ɽ��", 12, "����");

        set("age", 91);
        set("gender", "����");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("shen",150000);
        set("no_quest",1);

        set("con", 30);
        set("dex", 30);
        set("int", 40);
        set("str", 30);
	set("per", 24);
        set("max_jing", 6000);
        set("max_neili", 15000);
        set("max_qi", 7500);
        set("eff_jingli", 4000);
        set("neili", 15000);
        set("jiali", 100);
        set("combat_exp", 3000000);

        set_skill("sword",330);
        set_skill("force",200);
        set_skill("dodge",300);
        set_skill("parry",300);
        set_skill("dugu-jiujian",300);
        set_skill("huashan-shenfa",300);
        set_skill("huashan-jianfa",200);
        set_skill("zixia-gong",200);
        set_skill("zhengqi-jue",200);

        map_skill("force","zixia-gong");
        map_skill("sword","dugu-jiujian");
        map_skill("dodge","huashan-shenfa");
	map_skill("parry","dugu-jiujian");
	set_temp("apply/damage", 40);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);
	setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}

void attempt_apprentice(object ob)
{
	if ( ob->query("family/family_name") != "��ɽ��" && ob->query("is/huashan")==1 ) {
		message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
		command("slap "+ob->query("id"));
		return;
	}

        if (!ob->query("fengset")) {
		command("say ���ҿ��½�����Ե����λ" + RANK_D->query_respect(ob) +
                        "������ذɡ�");
		command("wave " + ob->query("id"));
		return;
        }
        if (ob->query("shen") < ob->query("combat_exp")) {
		command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
		return;
        }
        if ((int)ob->query_skill("zixia-gong",1)<180){
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�������ϼ�񹦵ȼ����ͣ��²��������Ҷ��¾Ž����衣");
                return;
        }
        if ((int)ob->query_skill("huashan-shenfa",1)<180){
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "����Ļ�ɽ���ȼ����ͣ��²��������Ҷ��¾Ž����衣");
                return;
        }
        if ((int)ob->query_skill("huashan-jianfa",1)<180){
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "����Ļ�ɽ�����ȼ����ͣ��²��������Ҷ��¾Ž����衣");
                return;
        }

        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        command("chat* ���ϸ��ֳ�һ˿Ц�ݣ�����"+ob->query("name")+"Ц�����һ�ɽ��������ˡ�");
        command("chat* nomatch feng");
        command("recruit " + ob->query("id"));
        ob->set("is/huashan",1);
        ob->set("title",HIW"��ɽ�ɷ����ﴫ��"NOR);
}
