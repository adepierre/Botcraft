#pragma once

#include "protocolCraft/NetworkType.hpp"

#include "botcraft/Network/DNS/DNSQuestion.hpp"
#include "botcraft/Network/DNS/DNSResourceRecord.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    class DNSMessage : public NetworkType
    {
    public:
        const std::vector<unsigned char>& GetIdentification() const
        {
            return identification;
        }

        char GetFlagQR() const
        {
            return qr;
        }

        char GetFlagOPCode() const
        {
            return opcode;
        }

        char GetFlagAA() const
        {
            return aa;
        }

        char GetFlagTC() const
        {
            return tc;
        }

        char GetFlagRD() const
        {
            return rd;
        }

        char GetFlagRA() const
        {
            return ra;
        }

        char GetFlagZ() const
        {
            return z;
        }

        char GetFlagRCode() const
        {
            return rcode;
        }

        short GetNumberQuestion() const
        {
            return number_question;
        }

        short GetNumberAnswer() const
        {
            return number_answer;
        }

        short GetNumberAuthority() const
        {
            return number_authority;
        }

        short GetNumberAdditionalRR() const
        {
            return number_additional_rr;
        }

        const std::vector<DNSQuestion>& GetQuestions() const
        {
            return questions;
        }

        const std::vector<DNSResourceRecord>& GetAnswers() const
        {
            return answers;
        }

        const std::vector<DNSResourceRecord>& GetAuthorities() const
        {
            return authorities;
        }

        const std::vector<DNSResourceRecord>& GetAdditionals() const
        {
            return additionals;
        }


        void SetIdentification(const std::vector<unsigned char>& identification_)
        {
            identification = identification_;
        }

        void SetFlagQR(const char qr_)
        {
            qr = qr_;
        }

        void SetFlagOPCode(const char opcode_)
        {
            opcode = opcode_;
        }

        void SetFlagAA(const char aa_)
        {
            aa = aa_;
        }

        void SetFlagTC(const char tc_)
        {
            tc = tc_;
        }

        void SetFlagRD(const char rd_)
        {
            rd = rd_;
        }

        void SetFlagRA(const char ra_)
        {
            ra = ra_;
        }

        void SetFlagZ(const char z_)
        {
            z = z_;
        }

        void SetFlagRCode(const char rcode_)
        {
            rcode = rcode_;
        }

        void SetNumberQuestion(const short number_question_)
        {
            number_question = number_question_;
        }

        void SetNumberAnswer(const short number_answer_)
        {
            number_answer = number_answer_;
        }

        void SetNumberAuthority(const short number_authority_)
        {
            number_authority = number_authority_;
        }

        void SetNumberAdditionalRR(const short number_additional_rr_)
        {
            number_additional_rr = number_additional_rr_;
        }

        void SetQuestions(const std::vector<DNSQuestion>& questions_)
        {
            questions = questions_;
        }

        void SetAnswers(const std::vector<DNSResourceRecord>& answers_)
        {
            answers = answers_;
        }

        void SetAuthorities(const std::vector<DNSResourceRecord>& authorities_)
        {
            authorities = authorities_;
        }

        void SetAdditionals(const std::vector<DNSResourceRecord>& additionals_)
        {
            additionals = additionals_;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            identification = ReadByteArray(iter, length, 2);
            char flags0 = ReadData<char>(iter, length);
            qr = (flags0 >> 7) & 0x01;
            opcode = (flags0 >> 3) & 0x0F;
            aa = (flags0 >> 2) & 0x01;
            tc = (flags0 >> 1) & 0x01;
            rd = flags0 & 0x01;

            char flags1 = ReadData<char>(iter, length);
            ra = (flags1 >> 7) & 0x01;
            z = (flags1 >> 4) & 0x07;
            rcode = flags1 & 0x0F;

            number_question = ReadData<short>(iter, length);
            number_answer = ReadData<short>(iter, length);
            number_authority = ReadData<short>(iter, length);
            number_additional_rr = ReadData<short>(iter, length);

            questions = std::vector<DNSQuestion>(number_question);
            for (int i = 0; i < number_question; ++i)
            {
                questions[i].Read(iter, length);
            }

            answers = std::vector<DNSResourceRecord>(number_answer);
            for (int i = 0; i < number_answer; ++i)
            {
                answers[i].Read(iter, length);
            }

            authorities = std::vector<DNSResourceRecord>(number_authority);
            for (int i = 0; i < number_authority; ++i)
            {
                authorities[i].Read(iter, length);
            }

            additionals = std::vector<DNSResourceRecord>(number_additional_rr);
            for (int i = 0; i < number_additional_rr; ++i)
            {
                additionals[i].Read(iter, length);
            }

        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteByteArray(identification, container);

            char flags0 = (qr << 7) | (opcode << 3) | (aa << 2) | (tc << 1) | rd;
            WriteData<char>(flags0, container);

            char flags1 = (ra << 7) | (z << 4) | opcode;
            WriteData<char>(flags1, container);

            WriteData<short>(number_question, container);
            WriteData<short>(number_answer, container);
            WriteData<short>(number_authority, container);
            WriteData<short>(number_additional_rr, container);

            for (int i = 0; i < questions.size(); ++i)
            {
                questions[i].Write(container);
            }

            for (int i = 0; i < answers.size(); ++i)
            {
                answers[i].Write(container);
            }

            for (int i = 0; i < authorities.size(); ++i)
            {
                authorities[i].Write(container);
            }

            for (int i = 0; i < additionals.size(); ++i)
            {
                additionals[i].Write(container);
            }
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["qr"] = qr;
            output["opcode"] = opcode;
            output["aa"] = aa;
            output["tc"] = tc;
            output["rd"] = rd;
            output["ra"] = ra;
            output["z"] = z;
            output["rcode"] = rcode;
            output["number_question"] = number_question;
            output["number_answer"] = number_answer;
            output["number_authority"] = number_authority;
            output["number_additional_rr"] = number_additional_rr;
            
            output["questions"] = Json::Array();
            for (int i = 0; i < number_question; ++i)
            {
                output["questions"].push_back(questions[i].Serialize());
            }

            output["answers"] = Json::Array();
            for (int i = 0; i < number_answer; ++i)
            {
                output["answers"].push_back(answers[i].Serialize());
            }

            output["authorities"] = Json::Array();
            for (int i = 0; i < number_authority; ++i)
            {
                output["authorities"].push_back(authorities[i].Serialize());
            }

            output["additionals"] = Json::Array();
            for (int i = 0; i < number_additional_rr; ++i)
            {
                output["additionals"].push_back(additionals[i].Serialize());
            }

            return output;
        }

    private:
        std::vector<unsigned char> identification;

        // Flags
        char qr;
        char opcode;
        char aa;
        char tc;
        char rd;
        char ra;
        char z;
        char rcode;


        short number_question;
        short number_answer;
        short number_authority;
        short number_additional_rr;

        std::vector<DNSQuestion> questions;
        std::vector<DNSResourceRecord> answers;
        std::vector<DNSResourceRecord> authorities;
        std::vector<DNSResourceRecord> additionals;

    };
}