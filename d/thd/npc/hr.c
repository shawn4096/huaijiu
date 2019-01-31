// /u/jpei/thd/npc/huangrong.c
// Modified by Numa 19990914

#include <ansi.h>
inherit NPC;
#include "nadir.c"
#include "thdjob.h"

int ask_husband();
int ask_job_s();
int ask_job();

void create()
{
        set_name("����", ({ "huang rong", "huang", "rong" }));
        set("long", 
                "���������䣬����ʮ��������ͣ�����ʤѩ�������ޱȣ���ɫ���������ɱ��ӡ�\n"
                "���������磬ȫ����£�ͷ��������һ���������Ȼ���⡣һ��װ��������Ůһ�㡣\n");
        set("gender", "Ů��");
        set("rank_info/rude", "С��Ů");
        set("age", 16);
        set("attitude","peaceful");
        set("str", 16);
        set("dex", 26);
        set("con", 18);
        set("int", 30);
        set("per", 50);
        set("shen_type", 0);

        set("jiali",50);
        set_skill("force", 70);
        set_skill("bihai-chaosheng", 65);
        set_skill("dodge", 90);
        set_skill("xiaoyaoyou", 80);
        set_skill("parry", 80);
        set_skill("strike", 85);
        set_skill("luoying-zhang", 80);
        set_skill("hand", 90);
        set_skill("lanhua-shou", 85);
        set_skill("finger", 60);
        set_skill("tanzhi-shentong", 50);
        set_skill("sword", 80);
        set_skill("yuxiao-jian", 70);
        set_skill("literate",220);
        set_skill("qimen-bagua", 200);

        map_skill("force", "bihai-chaosheng");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("strike", "luoying-zhang");
        map_skill("hand", "lanhua-shou");
        map_skill("finger", "tanzhi-shentong");
        map_skill("parry", "yuxiao-jian");
        map_skill("sword", "yuxiao-jian");
        prepare_skill("hand", "lanhua-shou");

        set("combat_exp", 450000);

        set("max_qi", 1200);
        set("max_jing", 600);
        set("neili", 650);
        set("max_neili", 650);

        set("inquiry", ([
                "name" : "���»��أ����һ�������Ů����",
                "rumors" : "�ҵ��������ﲼ��һ�������󣬱��뾫ͨ���Ե��������ͨ����",
                "here" : "��������һ����ˡ������Ǹ�С������������������ģ�������������ܲ�����ȫ�ˡ�",
                "����" : "�������Ȼ�е�ɵ�����ģ�����ȴ�����ĵġ�",
                "����" : "��������ʲô����",
                "��ҩʦ" : "�ҵ��������������Ĳ���ѧ���黭���壬������ԣ�ҽ�����࣬�������У���һ������",
                "����" : "�ҵ��������������Ĳ���ѧ���黭���壬������ԣ�ҽ�����࣬�������У���һ������",
                "��а" : "�ҵ��������������Ĳ���ѧ���黭���壬������ԣ�ҽ�����࣬�������У���һ������",
                "�ܲ�ͨ" : "���Ǹ�������ɽ����Ĺ�������һ���Ҵ���������ȥ�棬�������˰����ء�",
                "������" : "�ǵ��������Ե������ŵģ���ͬ�ķ����ʾس�ı仯���ÿ��سΪһ�ԣ����԰�˳���߶Ծ͹����ˡ�",
                "س" : "��Ҳ��֪������û�������ˡ�",
                "�ɷ�" : (: ask_husband :),
                "���" : (: ask_husband :),
                "����": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "jpei": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
// here add thd-job "ask huang" by Numa 19990911
                "ʦĸ": (: ask_job_s :),
                "��Ĺ": (: ask_job :),  
        ]) );
        
//here set do job's number
        set("thd/havejob",1);        

        setup();

        carry_object(__THD__"obj/gold_ribbon.c")->wear();
        carry_object("/d/city/obj/necklace.c")->wear();
        carry_object(__THD__"obj/white_cloth.c")->wear();
        carry_object(__THD__"obj/gold_belt.c")->wear();
        carry_object("/d/city/obj/goldring.c")->wear();
}

int ask_husband()
{
        object nvxu, user;
        object ob = this_player();
        string id;
        int user_load = 0;

        if (!(nvxu = find_object("/clone/npc/huang-son-in-law")))
                nvxu = load_object("/clone/npc/huang-son-in-law");
        id = nvxu->query("winner");
        if (id == ob->query("id")) {
                if (nvxu->query("death_count") < ob->query("death_count"))
                        say("���ص���ͷ��Ū���½ǣ�ʲô��Ҳ��˵��");
                else
                        message_vision(CYN"���غ��������ؿ���$N���۹⽿�����ޡ�\n"NOR, ob);
        }
        else {
                if (!(user = find_player(id))) {
                        user = new(LOADUSER_OB, id);
                        if (!user->restore()) {
                                say("���ص���ͷ��Ū���½ǣ�ʲô��Ҳ��˵��");
                                destruct(user);
                                return 1;
                        }
                        user_load = 1;
                }
                if (nvxu->query("death_count") < user->query("death_count"))
                        say("���ص���ͷ��Ū���½ǣ�ʲô��Ҳ��˵��");
                else
                        command("say �ҵ��ɷ����" + nvxu->query("name") + "��");
                if (user_load) destruct(user);
        }
        return 1;
}