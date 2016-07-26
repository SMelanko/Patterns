///////////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2016 Slava Melanko.
///
/// This code is licensed under the MIT License (MIT).
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
///////////////////////////////////////////////////////////////////////////////

#include "structural/Facade.h"

namespace pattern
{
namespace structural
{

bool FacilitiesFacade::CheckOnStatus() noexcept
{
	++_count;
	// The service request has been received.
	if (_state == Received) {
		++_state;
		// Redirect request to the engineer.
		_engineer.SubmitNetworkRequest();
		std::cout << std::endl << "Submitted to Facilities - " << _count
			 << " phone calls so far" << std::endl;
	} else if (_state == SubmitToEngineer) {
		// If engineer has done his work - redirect request to the electrician.
		if (_engineer.CheckOnStatus()) {
			++_state;
			_electrician.SubmitNetworkRequest();
			std::cout << "Submitted to Electrician - " << _count
				 << " phone calls so far" << std::endl;
		}
	} else if (_state == SubmitToElectrician) {
		// If electrician has done his work - redirect request to the technician.
		if (_electrician.CheckOnStatus()) {
			++_state;
			_technician.SubmitNetworkRequest();
			std::cout << "Submitted to MIS - " << _count
				 << " phone calls so far" << std::endl;
		}
	} else if (_state == SubmitToTechnician) {
		// If technician has done his work - request is finished.
		if (_technician.CheckOnStatus()) {
			return true;
		}
	}

	// Request is not finished yet.
	return false;
}

} // namespace structural
} // namespace pattern
