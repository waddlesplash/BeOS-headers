#ifndef C_SOUND_PLAYER_H

#define C_SOUND_PLAYER_H

#include <media2/MediaNode.h>

namespace B {
namespace Media2 {

class BMediaFormat;

class BSoundPlayer : public B::Support2::BAtom
{
	public:

		B_STANDARD_ATOM_TYPEDEFS(BSoundPlayer)

		typedef void (*BufferPlayerFunc) (void *, void *buffer, size_t size,
											const BMediaFormat &format);

	private:
		status_t mInitCheck;
		B::Media2::BMediaNode::sptr mImpl;

		BufferPlayerFunc mPlayBuffer;
		void *mCookie;

		mutable B::Support2::BLocker mLock;

		bool mRunning;
		thread_id mTID;
		volatile bool mDone;
							
		void Init (const BMediaConstraint &c, IMediaInput::sptr *);
	
		static int32 SoundPlayerThread (void *param);
		int32 SoundPlayerThread();
		
	public:		
		BSoundPlayer (B::Support2::IContext::sptr_ref context,
						const char *name,
						BufferPlayerFunc PlayBuffer,
						void *cookie = NULL);

		BSoundPlayer (B::Support2::IContext::sptr_ref context,
						const BMediaConstraint &c,
						const char *name,
						BufferPlayerFunc PlayBuffer,
						void *cookie = NULL);

		BSoundPlayer (IMediaInput::sptr *toInput,
						const char *name,
						BufferPlayerFunc PlayBuffer,
						void *cookie = NULL);

		BSoundPlayer (const BMediaConstraint &c,
						IMediaInput::sptr *toInput,
						const char *name,
						BufferPlayerFunc PlayBuffer,
						void *cookie = NULL);

		virtual ~BSoundPlayer();
		
		status_t InitCheck() const;
		BMediaFormat Format() const;
		
		status_t Start();
		status_t Stop();
		
		void SetBufferPlayer (BufferPlayerFunc PlayBuffer, void *cookie);

		BufferPlayerFunc BufferPlayer() const;
		void *Cookie() const;
};

} } // B::Media2

#endif
