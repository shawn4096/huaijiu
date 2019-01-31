// NPC: /d/huashan/npc/mu_renqing.c
// Date: Look 99/03/25

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void create()
{
        set_name("������",({"mu renqing","mu"}));
        set("nickname","����ԯ");
        set("long", "������ڽ���������Զ����������𣬻�ɽ������ԯ�����塣\n");
        set("age", 70);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 24);
        set("max_qi",7000);
        set("max_jing", 6800);
        set("eff_jingli", 3800);        
        set("max_neili", 14000);
        set("neili", 14500);
        set("jiali", 100);
        set("combat_exp", 2900000);
        set("score", 290000);
        set("chat_chance_combat",40);
        set("chat_msg_combat", ({
//  31                  (: perform_action, "strike.wuji" :),
        	(: perform_action, "cuff.leidong" :),
        }));
//  34          set_skill("strike", 290);
//  35          set_skill("hunyuan-zhang", 290);
        set_skill("sword",  230);
        set_skill("dodge",  290);
        set_skill("force",  200);
        set_skill("cuff", 290);
        set_skill("poyu-quan", 290);
        set_skill("huashan-jianfa", 230);
        set_skill("parry",  290);
        set_skill("literate", 100);
        set_skill("zixia-gong", 200);
        set_skill("huashan-shenfa", 290);
        set_skill("zhengqi-jue", 200);
  
        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
        map_skill("cuff","poyu-quan");
        map_skill("parry","huashan-jianfa");
//  52          map_skill("strike","hunyuan-zhang");
        map_skill("sword","huashan-jianfa");
//  54          prepare_skill("strike","hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");
	set_temp("apply/damage", 40);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);
        create_family("��ɽ��",12,"����");
        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}

void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family")) && (string)fam["family_name"] != "��ɽ��"  && (int)ob->query("is/huashan")==1 ) {
                message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
                command("slap "+ob->query("id"));
                return;
        }
        if ((int)ob->query("shen") <= 0) {
        command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
        command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
        "�Ƿ����ò�����");
        return;
        }
        if ((int)ob->query("max_pot") < 100) {
        command("say " + RANK_D->query_respect(ob) +
        "���ڲ���Ҫ����ָ������ȥ��������ʦ��ѧ��ȥ�ɡ�");
        return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        ob->set("is/huashan",1);
        command("recruit " + ob->query("id"));
}
